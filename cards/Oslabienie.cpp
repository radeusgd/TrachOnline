#include "cards/Oslabienie.hpp"

using namespace Cards;

string Oslabienie::getName(){
    return "oslabienie";
}

CardPtr Oslabienie::makeNew(){
    return make_shared<Oslabienie>();
}

void Oslabienie::reset(){
    Feature::reset();
    value = 1;
}

void Oslabienie::apply(GameServer::Player& player){
    player.maxHP-=value;
}

void Oslabienie::beforeEquip(GameServer::Player& player, GameServer& game){
    player.HP-=value;
    player.clampHP();
}
