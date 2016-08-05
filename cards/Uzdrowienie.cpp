#include "cards/Uzdrowienie.hpp"
#include "GameServer.hpp"

using namespace Cards;

string Uzdrowienie::getName(){
    return "uzdrowienie";
}

bool Uzdrowienie::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr Uzdrowienie::makeNew(){
    return make_shared<Uzdrowienie>();
}

void Uzdrowienie::reset(){
    Targetable::reset();
    priority = 0;
    value = 1;
    active = true;
}

void Uzdrowienie::played(GameServer& game){
    game.players[to.playerId].HP+=value;
    game.players[to.playerId].clampHP();
}
