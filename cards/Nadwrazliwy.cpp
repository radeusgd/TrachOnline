#include "cards/Nadwrazliwy.hpp"

using namespace Cards;

string Nadwrazliwy::getName(){
    return "nadwrazliwy";
}

CardPtr Nadwrazliwy::makeNew(){
    return make_shared<Nadwrazliwy>();
}

void Nadwrazliwy::reset(){
    Feature::reset();
    value = 2;
}

void Nadwrazliwy::apply(GameServer::Player& player){
    player.incomingDamageMod*=float(value);
}
