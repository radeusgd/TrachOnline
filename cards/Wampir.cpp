#include "cards/Wampir.hpp"

using namespace Cards;

string Wampir::getName(){
    return "wampir";
}

CardPtr Wampir::makeNew(){
    return make_shared<Wampir>();
}

vector<CardPtr>& Wampir::getAppliedCards(){
    return appliedCards;
}

int& Wampir::getOwnerId(){
    return ownerid;
}

int& Wampir::getCUID(){
    return cuid;
}

bool& Wampir::getActiveState(){
    return active;
}

void Wampir::apply(GameServer::Player& player){
    player.wampir=true;
}
