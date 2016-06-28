#include "cards/Superwytrzymaly.hpp"

using namespace Cards;

string Superwytrzymaly::getName(){
    return "superwytrzymaly";
}

CardPtr Superwytrzymaly::makeNew(){
    return make_shared<Superwytrzymaly>();
}

vector<CardPtr>& Superwytrzymaly::getAppliedCards(){
    return appliedCards;
}

int& Superwytrzymaly::getOwnerId(){
    return ownerid;
}

int& Superwytrzymaly::getCUID(){
    return cuid;
}

bool& Superwytrzymaly::getActiveState(){
    return active;
}

void Superwytrzymaly::reset(){
    Feature::reset();
    value = 3;
}

void Superwytrzymaly::apply(GameServer::Player& player){
    player.maxHP+=value;
}

void Superwytrzymaly::afterEquip(GameServer::Player& player, GameServer& game){
    player.HP+=value;
    player.clampHP();
}
