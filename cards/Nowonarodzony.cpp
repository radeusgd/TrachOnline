#include "cards/Nowonarodzony.hpp"
#include "GameServer.hpp"
using namespace Cards;

string Nowonarodzony::getName(){
    return "nowonarodzony";
}

bool Nowonarodzony::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr Nowonarodzony::makeNew(){
    return make_shared<Nowonarodzony>();
}

vector<CardPtr>& Nowonarodzony::getAppliedCards(){
    return appliedCards;
}
int& Nowonarodzony::getOwnerId(){
    return ownerid;
}
int& Nowonarodzony::getCUID(){
    return cuid;
}

bool& Nowonarodzony::getActiveState(){
    return active;
}

void Nowonarodzony::played(GameServer& game){
    game.players[to].prepare();
    for(auto c : game.players[to].hand) game.recycleCard(c);
    game.players[to].hand.clear();
    game.players[to].HP = game.players[to].maxHP;
    game.fillCards(game.players[to]);
    
}
