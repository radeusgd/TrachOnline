#include "cards/WymianaKart.hpp"
#include "GameServer.hpp"

using namespace Cards;

string WymianaKart::getName(){
    return "wymiana_kart";
}

bool WymianaKart::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr WymianaKart::makeNew(){
    return make_shared<WymianaKart>();
}

void WymianaKart::played(GameServer& game){
    int to = WymianaKart::to.playerId;//TODO get rid of shadowing
    for(auto c : game.players[to].hand) game.recycleCard(c);
    game.players[to].hand.clear();
    game.fillCards(game.players[to]);
}
