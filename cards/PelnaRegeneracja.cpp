#include "cards/PelnaRegeneracja.hpp"
#include "GameServer.hpp"

using namespace Cards;

string PelnaRegeneracja::getName(){
    return "pelna_regeneracja";
}

bool PelnaRegeneracja::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr PelnaRegeneracja::makeNew(){
    return make_shared<PelnaRegeneracja>();
}

void PelnaRegeneracja::reset(){
    Targetable::reset();
    priority = 0;
    active = true;
}

void PelnaRegeneracja::played(GameServer& game){
    game.players[to].HP=game.players[to].maxHP;
}
