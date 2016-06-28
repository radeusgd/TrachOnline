#include "cards/Oslabienie.hpp"

using namespace Cards;

string Oslabienie::getName(){
    return "oslabienie";
}

CardPtr Oslabienie::makeNew(){
    return make_shared<Oslabienie>();
}

vector<CardPtr>& Oslabienie::getAppliedCards(){
    return appliedCards;
}

int& Oslabienie::getOwnerId(){
    return ownerid;
}

int& Oslabienie::getCUID(){
    return cuid;
}

bool& Oslabienie::getActiveState(){
    return active;
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
