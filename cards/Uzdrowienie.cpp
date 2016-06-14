#include "cards/Uzdrowienie.hpp"
#include "GameServer.hpp"

using namespace Cards;

string Uzdrowienie::getName(){
    return "uzdrowienie";
}

bool Uzdrowienie::canBePlayedAt(CardPtr card){
    if(card==nullptr) return true;
    return false;
}

CardPtr Uzdrowienie::makeNew(){
    return make_shared<Uzdrowienie>();
}

vector<CardPtr>& Uzdrowienie::getAppliedCards(){
    return appliedCards;
}

int& Uzdrowienie::getCUID(){
    return cuid;
}

bool& Uzdrowienie::getActiveState(){
    return active;
}

void Uzdrowienie::prepare(){
    value = 1;
    active = true;
}

void Uzdrowienie::played(GameServer& game){
    game.players[to].HP+=value;
    game.players[to].clampHP();
}
