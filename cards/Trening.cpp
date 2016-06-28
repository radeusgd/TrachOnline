#include "cards/Trening.hpp"

using namespace Cards;

string Trening::getName(){
    return "trening";
}

CardPtr Trening::makeNew(){
    return make_shared<Trening>();
}

vector<CardPtr>& Trening::getAppliedCards(){
    return appliedCards;
}

int& Trening::getOwnerId(){
    return ownerid;
}

int& Trening::getCUID(){
    return cuid;
}

bool& Trening::getActiveState(){
    return active;
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
