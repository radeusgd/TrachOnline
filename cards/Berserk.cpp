#include "cards/Berserk.hpp"

using namespace Cards;

string Berserk::getName(){
    return "berserk";
}

CardPtr Berserk::makeNew(){
    return make_shared<Berserk>();
}

vector<CardPtr>& Berserk::getAppliedCards(){
    return appliedCards;
}

int& Berserk::getOwnerId(){
    return ownerid;
}

int& Berserk::getCUID(){
    return cuid;
}

bool& Berserk::getActiveState(){
    return active;
}

void Berserk::reset(){
    Feature::reset();
    value = 2;
}

void Berserk::apply(GameServer::Player& player){
    player.outgoingDamageMod*=float(value);
}
