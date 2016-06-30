#include "cards/Trening.hpp"

using namespace Cards;

string Trening::getName(){
    return "trening";
}

CardPtr Trening::makeNew(){
    return make_shared<Trening>();
}

void Trening::reset(){
    Feature::reset();
    value = 1;
}

void Trening::apply(GameServer::Player& player){
    player.maxHP+=value;
}

void Trening::afterEquip(GameServer::Player& player, GameServer& game){
    player.HP+=value;
    player.clampHP();
}
