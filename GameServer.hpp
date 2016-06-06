#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/WebSocket.h"
#include "json.hpp"
#include <set>
#include <string>

#include "Message.hpp"
#include "cards/BaseCard.hpp"

using namespace std;
using namespace seasocks;
using namespace nlohmann;

struct GameServer : WebSocket::Handler {
	struct User{
		User(WebSocket* ws);
		User();
		string nickname = "???";
		WebSocket* ws;
		int playerId=-1;
	};
    struct Player{
        WebSocket* ws;//for id

        int maxHP=5;
        int HP=5;
        int handCards = 5;
        vector<shared_ptr<BaseCard>> hand;
        //TODO tablecards etc.
    };
	
	//helper functions
    void onConnect(WebSocket *socket) override;
    void onData(WebSocket * conn, const char *data) override;
    void onDisconnect(WebSocket *socket) override;
	
	void broadcast(const Message& m);
	void send(WebSocket* c, const Message& m);
	
	//logic implementation
	map<WebSocket*,User> connections;
	int afkCount;
	map<string,function<void(WebSocket*,json)>> handlers;
	
    enum State{
		WAITING, PLAYING
	} state = WAITING;
    GameServer();
	void updateUsers();
	
	void resetGame();
	void startPlaying();
    
    vector<Player> players;
    int currentTurnPid=0;
    vector<shared_ptr<BaseCard>> stack, trash;
    void fillCards(Player& p);

    void updateCards(Player& p);
    
    void nextTurn(int pid=-1);
};

#endif
