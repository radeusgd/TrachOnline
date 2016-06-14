#include "GameServer.hpp"
#include "Deck.hpp"
#include "cards/Targetable.hpp"
#include "cards/Playable.hpp"

GameServer::User::User(WebSocket* ws) : ws(ws) {}
GameServer::User::User(){}

void GameServer::Player::dealDamage(int damage){
    //TODO modificators
    HP-=damage;
    clampHP();
}

void GameServer::Player::clampHP(){
    if(HP<0) HP=0;
    if(HP>maxHP) HP=maxHP;
}

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

void GameServer::addCardToTable(CardPtr card){
    card->getCUID() = turnTable.size();
    turnTable.push_back(card);
}

GameServer::GameServer(){
    commands["give"] = [&](WebSocket* conn, string args){
        try{
            Player& p = getPlayer(conn);
            CardPtr card = makeCardFromName(args);
            if(card!=nullptr){
                p.hand.push_back(card);
                updateCards(p);
            }
        }catch(...){

        }
    };
    commands["healall"] = [&](WebSocket* conn, string args){
        for(Player& p : players){
            p.HP = p.maxHP;
        }
    };
	handlers["login"] = [&](WebSocket* conn, json data){
		connections[conn].nickname = data["nickname"];
		updateUsers();
	};
	handlers["requestStart"] = [&](WebSocket* conn, json data){
		startPlaying();
	};
    handlers["chatMessage"] = [&](WebSocket* conn, json data){
        string text = data;
        Message m;
        m.name="chatMessage";
        m.data = connections[conn].nickname + ": " + text;
        if(text.length()==0) return;//empty message
        if(text[0]=='/'){//command
            text = text.substr(1);
            int space = text.find(' ');
            if(space==string::npos){
               space=text.length(); 
            }
            string cmd = text.substr(0,space);
            string args = "";
            if(space+1<text.length())   args=text.substr(space+1);
            if(commands[cmd]){
                commands[cmd](conn,args);
                m.data = connections[conn].nickname + ": " + text +  " => OK";
            }else{
                m.data = connections[conn].nickname + ": " + text +  " => Unknown command!";
            }
            send(conn,m);   
        }
        else{
            broadcast(m);
        }
	};
    handlers["playCard"] = [&](WebSocket* conn, json data){
        struct CannotDoThat{};
        try{
            Player& p = getPlayer(conn);
            int cid = data["id"];
            if(cid<0 || cid>= p.hand.size()) throw CannotDoThat();
    	    CardPtr card = p.hand[cid];
            auto targetable = dynamic_pointer_cast<Cards::Targetable>(card);
            if(targetable!=nullptr){
                //card is Targetable
                targetable->from = connections[conn].playerId;
                targetable->to = data["target"];
                //TODO from->canInfluence(to) - for things like KrotkieRaczki or RozdwojenieJazni
            }
            int attache = data["attachTo"];
            if(attache<0){
                if(!card->canBePlayedAt(nullptr)) throw CannotDoThat();//check if the card can be played as base card
                tableBaseCards.push_back(card);
            }else{
                if(attache>=turnTable.size()) throw CannotDoThat();//id out of range (error)
                if(!card->canBePlayedAt(turnTable[attache])) throw CannotDoThat();//check if card can be attached to this one
                turnTable[attache]->getAppliedCards().push_back(card);
                turnTable[attache]->refresh(*this);//refresh parent after attaching a card to it
            }
            addCardToTable(card);
            p.hand.erase(p.hand.begin()+cid);//take away this card from players hand
            cout<<connections[conn].playerId<<" played "<<card->getName()<<endl;
            card->refresh(*this);
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
        catch(CannotDoThat e){
            try{
                Player& p = getPlayer(conn);
                updateCards(p);
            }catch(...){}
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
        card->refresh(*this);//prepare card for final run
        shared_ptr<Cards::Playable> playable = dynamic_pointer_cast<Cards::Playable>(card);
        if(playable && playable->getActiveState()){
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
           vector<CardPtr> newTrash;
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
        //FIXME loop if all men die
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
   m.data = json::array();
   for(auto& card : tableBaseCards){
        m.data.push_back(card->jsonify());
        cout<<"TableCard "<<card->getName()<<endl;
   }
   cout<<"Sending cards: "<<m.data<<endl;
   broadcast(m);
}
