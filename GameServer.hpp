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
        int avatar;
		WebSocket* ws;
		int playerId=-1;
	};
    struct Player{
        WebSocket* ws;//for id
        int id;
        int maxHP;
        int HP;
        int handCards;
        float incomingDamageMod;
        float outgoingDamageMod;
				bool wampir;

        int calculateDamage(int base, float mod);
        vector<CardPtr> hand;
        vector<CardPtr> equipment;
				Player();
        void prepare();
        void refresh(GameServer& game);
        int receiveDamage(int damage);
        int giveDamage(int damage);
				void givenDamage(int damage);
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
    int winner;
    Player& getPlayer(WebSocket* ws);
    int livingPlayersCount();
    int currentTurnPid=0;
    bool turnsReversed;
    int skipped=0;
    vector<CardPtr> stack, trash;
    void fillCards(Player& p);

    void updateCards(Player& p);

    /** runs all cards on table, removes them and starts the new turn */
    void flushTable();

    struct CannotDoThat{};
    void playCard(Player& p, CardPtr card, json data, set<int>& usedCards);

    void recycleCard(CardPtr card);
    void addCardToTable(CardPtr card);
    void nextTurn(int pid=-1);

    vector<CardPtr> turnTable;
    vector<CardPtr> tableBaseCards;
    void updateTurnTable();
    void executeTurnBased();
		void disposeEquipped(Player& p, int eqn, string type);


};

#endif
