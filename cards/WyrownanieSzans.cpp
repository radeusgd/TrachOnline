#include "cards/WyrownanieSzans.hpp"
#include "GameServer.hpp"

using namespace Cards;

string WyrownanieSzans::getName(){
    return "wyrownanie_szans";
}

bool WyrownanieSzans::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr WyrownanieSzans::makeNew(){
    return make_shared<WyrownanieSzans>();
}

void WyrownanieSzans::played(GameServer& game){
    int minHP=5;
    for(GameServer::Player& p : game.players){
        if(p.HP>0 && p.HP<minHP) minHP=p.HP;
    }
    for(GameServer::Player& p : game.players){
        if(p.HP>0) p.HP=minHP;
    }
    for(GameServer::Player& p : game.players){
        for(auto& c:p.equipment){
          game.recycleCard(c);
        }
        p.equipment.clear();
    }
    for(GameServer::Player& p : game.players){
        p.refresh(game);
    }
}
