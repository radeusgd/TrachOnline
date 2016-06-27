#include "cards/Gruboskorny.hpp"

using namespace Cards;

string Gruboskorny::getName(){
    return "gruboskorny";
}

CardPtr Gruboskorny::makeNew(){
    return make_shared<Gruboskorny>();
}

vector<CardPtr>& Gruboskorny::getAppliedCards(){
    return appliedCards;
}

int& Gruboskorny::getOwnerId(){
    return ownerid;
}

int& Gruboskorny::getCUID(){
    return cuid;
}

bool& Gruboskorny::getActiveState(){
    return active;
}

void Gruboskorny::reset(){
    Feature::reset();
    value = 2;
}

void Gruboskorny::apply(GameServer::Player& player){
    player.incomingDamageMod/=float(value);
}
