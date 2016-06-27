#include "cards/Nadwrazliwy.hpp"

using namespace Cards;

string Nadwrazliwy::getName(){
    return "nadwrazliwy";
}

CardPtr Nadwrazliwy::makeNew(){
    return make_shared<Nadwrazliwy>();
}

vector<CardPtr>& Nadwrazliwy::getAppliedCards(){
    return appliedCards;
}

int& Nadwrazliwy::getOwnerId(){
    return ownerid;
}

int& Nadwrazliwy::getCUID(){
    return cuid;
}

bool& Nadwrazliwy::getActiveState(){
    return active;
}

void Nadwrazliwy::reset(){
    Feature::reset();
    value = 2;
}

void Nadwrazliwy::apply(GameServer::Player& player){
    player.incomingDamageMod*=float(value);
}
