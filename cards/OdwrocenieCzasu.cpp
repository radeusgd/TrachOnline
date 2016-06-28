#include "cards/OdwrocenieCzasu.hpp"
#include "GameServer.hpp"

using namespace Cards;

string OdwrocenieCzasu::getName(){
    return "odwrocenie_czasu";
}

CardPtr OdwrocenieCzasu::makeNew(){
    return make_shared<OdwrocenieCzasu>();
}

vector<CardPtr>& OdwrocenieCzasu::getAppliedCards(){
    return appliedCards;
}

int& OdwrocenieCzasu::getOwnerId(){
    return ownerid;
}

int& OdwrocenieCzasu::getCUID(){
    return cuid;
}

bool& OdwrocenieCzasu::getActiveState(){
    return active;
}

void OdwrocenieCzasu::played(GameServer& game){
    game.turnsReversed = !game.turnsReversed;//reverse time
}
