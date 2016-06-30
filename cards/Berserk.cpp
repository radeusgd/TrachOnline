#include "cards/Berserk.hpp"

using namespace Cards;

string Berserk::getName(){
    return "berserk";
}

CardPtr Berserk::makeNew(){
    return make_shared<Berserk>();
}

void Berserk::reset(){
    Feature::reset();
    value = 2;
}

void Berserk::apply(GameServer::Player& player){
    player.outgoingDamageMod*=float(value);
}
