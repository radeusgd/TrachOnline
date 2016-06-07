#include "cards/Pustak.hpp"

using namespace Cards;

string Pustak::getName(){
    return "pustak";
}

bool Pustak::canBePlayedAt(CardPtr card){
    if(card==nullptr) return true;
    return false;
}

CardPtr Pustak::makeNew(){
    return make_shared<Pustak>();
}

vector<CardPtr>& Pustak::getAppliedCards(){
    return appliedCards;
}

int& Pustak::getCUID(){
    return cuid;
}

void Pustak::played(GameServer& game){
    //does nothing
}
