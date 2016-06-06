#include "GameServer.hpp"
#include "Deck.hpp"

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

void GameServer::fillCards(Player& p){
    if(p.HP<=0) return;//if player is dead, do not attempt
    while(p.hand.size()<p.handCards){
       if(stack.size()==0){
           //take all elements from trash except for the last 10
           for(int i=0;i<trash.size()-10;++i) stack.push_back(trash[i]);

           //remove all elements from trash, leave just the last 10 (make new trash, put last elements, swap trashes)
           vector<shared_ptr<BaseCard>> newTrash;
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
    Message m;
    m.name="updateTurn";
    m.data["currentPid"] = currentTurnPid;
    broadcast(m);
    cout<<"It's "<<connections[players[currentTurnPid].ws].nickname<<" turn"<<endl;
}
