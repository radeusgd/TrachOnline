#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/WebSocket.h"
#include "json.hpp"
#include <set>
#include <string>
#include <chrono>

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
        vector<CardPtr> hand;
        //TODO tablecards etc.
        //
        void dealDamage(int damage);
        void clampHP();
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
	map<string,function<void(WebSocket*,string)>> commands;
	
    enum State{
		WAITING, PLAYING
	} state = WAITING;
    GameServer();
	void updateUsers();
	
	void resetGame();
	void startPlaying();

    void tick();

    chrono::time_point<chrono::steady_clock> lastActionTime;
    enum Mode{
        NONE,PLAY,RESPONSE
    } mode=NONE;

    
    vector<Player> players;
    Player& getPlayer(WebSocket* ws);
    int currentTurnPid=0;
    int skipped=0;
    vector<CardPtr> stack, trash;
    void fillCards(Player& p);

    void updateCards(Player& p);
    
    /** runs all cards on table, removes them and starts the new turn */
    void flushTable();
    void addCardToTable(CardPtr card);
    void nextTurn(int pid=-1);

    vector<CardPtr> turnTable;
    vector<CardPtr> tableBaseCards;
    void updateTurnTable();

};

#endif
