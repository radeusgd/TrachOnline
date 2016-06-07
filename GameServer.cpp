#include "GameServer.hpp"
#include "Deck.hpp"
#include "cards/Targetable.hpp"
#include "cards/Playable.hpp"

GameServer::User::User(WebSocket* ws) : ws(ws) {}
GameServer::User::User(){}

void GameServer::onConnect(WebSocket *socket) 
{
	if(state == PLAYING){
		send(socket,Message("error","Game in progress. Spectating not supported").toText());
		socket->close();
		return;
	}
	connections.insert(make_pair(socket,User(socket)));
	updateUsers();
}
void GameServer::onData(WebSocket * conn, const char *data) 
{
	Message m(data);
	if(handlers[m.name]){
		handlers[m.name](conn,m.data);
	}
}
void GameServer::onDisconnect(WebSocket *socket) 
{
	if(state == WAITING)
		connections.erase(socket);
	else if(connections.find(socket)!=connections.end()){
		connections[socket].nickname = connections[socket].nickname + " (disconnected)";
		connections[socket].ws = nullptr;
        int pid = connections[socket].playerId;
        if(pid>=0){
            players[pid].HP = 0;
        }
		afkCount++;
		if(afkCount==connections.size()){
			cout<<"All players disconnected. Resetting game state."<<endl;
			connections.clear();
			afkCount = 0;
			resetGame();
		}
	}
	updateUsers();
}

void GameServer::broadcast(const Message& m){
	string data = m.toText();
	for (auto c : connections){
		if(c.second.ws!=nullptr)
			c.second.ws->send(data.c_str());
	}
}
void GameServer::send(WebSocket* c, const Message& m){
	if(c==nullptr) return;
	c->send(m.toText().c_str());
}

GameServer::GameServer(){
	handlers["login"] = [&](WebSocket* conn, json data){
		connections[conn].nickname = data["nickname"];
		updateUsers();
	};
	handlers["requestStart"] = [&](WebSocket* conn, json data){
		startPlaying();
	};
    handlers["playCard"] = [&](WebSocket* conn, json data){
        try{
            Player& p = getPlayer(conn);
            int cid = data["id"];
            if(cid<0 || cid>= p.hand.size()) return;
    	    Cards::CardPtr card = p.hand[cid];
            auto targetable = dynamic_pointer_cast<Cards::Targetable>(card);
            if(targetable!=nullptr){
                //card is Targetable
                targetable->from = connections[conn].playerId;
                targetable->to = data["target"];
            }
            card->getCUID() = turnTable.size();
            turnTable.push_back(card);
            int attache = data["attachTo"];
            if(attache<0){//new card TODO check permissions!!!
                tableBaseCards.push_back(card);
            }else{//TODO check permissions!!! FIXME
                if(attache<0||attache>=turnTable.size()) return;
                turnTable[attache]->getAppliedCards().push_back(card);
            }
            p.hand.erase(p.hand.begin()+cid);//take away this card from players hand
            cout<<connections[conn].playerId<<" zagral "<<card->getName()<<endl;
            fillCards(p);
            updateTurnTable();
            mode = RESPONSE;
            lastActionTime = chrono::steady_clock::now();
        }
        catch(string s){
            cout<<"Exception: "<<s<<endl;
        }
        catch(std::domain_error e){
            cout<<"Domain error"<<endl;
        }
        catch(std::out_of_range e){
            cout<<"Out of range error"<<endl;
        }
        catch(...){
            cout<<"Unknown exception!"<<endl;
        }
    };

}
void GameServer::updateUsers(){
	Message m;
	m.name = "updateUsers";
	for(auto& c : connections){
		json u;
		u["id"] = c.second.playerId;
		u["username"] = c.second.nickname;
        u["avatar"] = c.second.playerId;
        if(c.second.playerId>=0){
            Player& p = players[c.second.playerId];
            u["maxHP"] = p.maxHP;
            u["HP"] = p.HP;
            u["cardsAmount"] = p.handCards;
        }
		m.data.push_back(u);
	}
	broadcast(m);
}

void GameServer::resetGame(){
	state = WAITING;
    mode = NONE;
    players.clear();
}
void GameServer::startPlaying(){
	cout<<"Starting the game"<<endl;
	state = PLAYING;

    trash.clear();
    stack = makeDeck();
    
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(stack.begin(),stack.end(),g);

	int count = 0;
	for(auto c : connections){
		if(c.second.nickname!="???") count++;
	}
    players.resize(count);
	int pid = 0;
	for(auto& c : connections){
		if(c.second.nickname!="???"){
            c.second.playerId = pid++;
            players[c.second.playerId].ws = c.first;
            json init;
            init["id"] = c.second.playerId;
            init["avatar"] = c.second.playerId;//TODO choosing avatars?
            init["username"] = c.second.nickname;
            send(c.second.ws,Message("init",init));
            fillCards(players[c.second.playerId]);//give starting cards
        }
	}
	updateUsers();
    nextTurn(0);//TODO pustak
}

void GameServer::tick(){
   auto interval = chrono::seconds(5);
   switch(mode){
        case NONE: 
            //cout<<"Currently not running the game. Skipping the tick."<<endl;    
        return;
        case PLAY: interval = chrono::seconds(10); break;
        case RESPONSE: interval = chrono::seconds(7); break;
   }
   auto elapsed = chrono::steady_clock::now() - lastActionTime;
   //cout<<"Time elapsed: "<<chrono::duration_cast<chrono::milliseconds>(elapsed).count()<<"ms "<<endl;
   if(elapsed >= interval){
        /*switch(mode){
            case PLAY:
                
                break;
            case RESPONSE:
                
                break;
        }*/
       if(state!=PLAYING) return;
       cout<<"Starting next turn due to inactivity!"<<endl;
       flushTable();
   }else{
        auto left = interval - elapsed;
        Message m;
        m.name = "updateTiming";
        m.data = chrono::duration_cast<chrono::seconds>(left).count();
        //cout<<m.data<<"s left"<<endl;
        broadcast(m);
   }
}

void GameServer::flushTable(){
    for(auto& card : tableBaseCards){
        shared_ptr<Cards::Playable> playable = dynamic_pointer_cast<Cards::Playable>(card);
        if(playable){
            playable->played(*this);
        }
    }
    tableBaseCards.clear();
    turnTable.clear();
    nextTurn();
}

GameServer::Player& GameServer::getPlayer(WebSocket* ws){
    int pid = connections[ws].playerId;
    if(pid<0||pid>=players.size()) throw "invalid player";
    return players[pid];
}

void GameServer::fillCards(Player& p){
    if(p.HP<=0) return;//if player is dead, do not attempt
    while(p.hand.size()<p.handCards){
       if(stack.size()==0){
           //take all elements from trash except for the last 10
           for(int i=0;i<trash.size()-10;++i) stack.push_back(trash[i]);

           //remove all elements from trash, leave just the last 10 (make new trash, put last elements, swap trashes)
           vector<Cards::CardPtr> newTrash;
           for(int i=trash.size()-10;i<trash.size();++i) newTrash.push_back(trash[i]);
           swap(trash,newTrash);

           //shuffle the stack
           std::random_device rd;
           std::mt19937 g(rd());
           shuffle(stack.begin(),stack.end(),g);
       }
       p.hand.push_back(stack.back());
       stack.pop_back();
    }
    updateCards(p);
}

void GameServer::updateCards(Player& p){
 //   cout<<"Sending "<<p.hand.size()<<" cards"<<endl;
    Message m;
    m.name = "updateCards";
    for(auto& c : p.hand){
        m.data.push_back(c->getName());
    }
    send(p.ws,m);
}

void GameServer::nextTurn(int pid){
    if(pid<0){
        pid = (currentTurnPid+1)%players.size();
        while(players[pid].HP<=0) pid = (pid+1)%players.size();
    }
    currentTurnPid = pid;
    turnTable.clear();
    updateTurnTable();
    Message m;
    m.name="updateTurn";
    m.data["currentPid"] = currentTurnPid;
    broadcast(m);
    updateUsers();//TODO consider moving elsewhere
    mode = PLAY;
    lastActionTime = chrono::steady_clock::now();
    cout<<"It's "<<connections[players[currentTurnPid].ws].nickname<<" turn"<<endl;
}

void GameServer::updateTurnTable(){//turning tables
   Message m;
   m.name="updateTurnTable";
   for(auto& card : turnTable){
        m.data.push_back(card->jsonify());
   }
   broadcast(m);
}
