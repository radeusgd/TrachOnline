#include "cards/Kot.hpp"

using namespace Cards;

string Kot::getName(){
    return "kot";
}

CardPtr Kot::makeNew(){
    return make_shared<Kot>();
}

void Kot::reset(){
    Feature::reset();
    value = 9;
}

void Kot::apply(GameServer::Player& player){
    player.maxHP=value;
}

void Kot::afterEquip(GameServer::Player& player, GameServer& game){
    player.HP=value;
    player.clampHP();
}
