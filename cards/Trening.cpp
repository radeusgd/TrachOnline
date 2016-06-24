#include "cards/Trening.hpp"

using namespace Cards;

string Trening::getName(){
    return "trening";
}

bool Trening::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr Trening::makeNew(){
    return make_shared<Trening>();
}

vector<CardPtr>& Trening::getAppliedCards(){
    return appliedCards;
}

int& Trening::getOwnerId(){

}

int& Trening::getCUID(){
    return cuid;
}

bool& Trening::getActiveState(){
    return active;
}

