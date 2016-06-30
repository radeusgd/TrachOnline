#include "cards/OdwrocenieCzasu.hpp"
#include "GameServer.hpp"

using namespace Cards;

string OdwrocenieCzasu::getName(){
    return "odwrocenie_czasu";
}

CardPtr OdwrocenieCzasu::makeNew(){
    return make_shared<OdwrocenieCzasu>();
}

void OdwrocenieCzasu::played(GameServer& game){
    game.turnsReversed = !game.turnsReversed;//reverse time
}
