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

vector<CardPtr>& WyrownanieSzans::getAppliedCards(){
    return appliedCards;
}

int& WyrownanieSzans::getOwnerId(){
    return ownerid;
}

int& WyrownanieSzans::getCUID(){
    return cuid;
}

bool& WyrownanieSzans::getActiveState(){
    return active;
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
