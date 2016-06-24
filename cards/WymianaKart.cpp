#include "cards/WymianaKart.hpp"
#include "GameServer.hpp"

using namespace Cards;

string WymianaKart::getName(){
    return "wymiana_kart";
}

bool WymianaKart::canBePlayedAt(CardPtr card){
    if(card==nullptr) return true;
    return false;
}

CardPtr WymianaKart::makeNew(){
    return make_shared<WymianaKart>();
}

vector<CardPtr>& WymianaKart::getAppliedCards(){
    return appliedCards;
}

int& WymianaKart::getOwnerId(){
    return ownerid;
}
int& WymianaKart::getCUID(){
    return cuid;
}

bool& WymianaKart::getActiveState(){
    return active;
}

void WymianaKart::played(GameServer& game){
    for(auto c : game.players[to].hand) game.recycleCard(c);
    game.players[to].hand.clear();
    game.fillCards(game.players[to]);
}
