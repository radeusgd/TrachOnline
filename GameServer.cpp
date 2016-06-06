#include "GameServer.hpp"

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
        u["avatar"] = c.second.playerId;//TODO avatars
        u["maxHP"] = 0;//TODO stats
        u["HP"] = 0;
        u["cardsAmount"] = 0;
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
	int count = 0;
	for(auto c : connections){
		if(c.second.nickname!="???") count++;
	}
	//players.resize(count);
	int pid = 0;
	for(auto& c : connections){
		if(c.second.nickname!="???"){
            c.second.playerId = pid++;
            json init;
            init["id"] = c.second.playerId;
            init["avatar"] = c.second.playerId;//TODO choosing avatars?
            init["username"] = c.second.nickname;
            send(c.second.ws,Message("init",init));
        }
	}
	updateUsers();
}

