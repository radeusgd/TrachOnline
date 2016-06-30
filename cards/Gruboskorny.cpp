#include "cards/Gruboskorny.hpp"

using namespace Cards;

string Gruboskorny::getName(){
    return "gruboskorny";
}

CardPtr Gruboskorny::makeNew(){
    return make_shared<Gruboskorny>();
}

void Gruboskorny::reset(){
    Feature::reset();
    value = 2;
}

void Gruboskorny::apply(GameServer::Player& player){
    player.incomingDamageMod/=float(value);
}
