#include "cards/DezaktywacjaKarty.hpp"

using namespace Cards;

string DezaktywacjaKarty::getName(){
    return "dezaktywacja_karty";
}

bool DezaktywacjaKarty::canBePlayedAt(CardPtr card, GameServer* game){
    return true;
}

CardPtr DezaktywacjaKarty::makeNew(){
    return make_shared<DezaktywacjaKarty>();
}

vector<CardPtr>& DezaktywacjaKarty::getAppliedCards(){
    return appliedCards;
}

int& DezaktywacjaKarty::getOwnerId(){
    return ownerid;
}

int& DezaktywacjaKarty::getCUID(){
    return cuid;
}

bool& DezaktywacjaKarty::getActiveState(){
    return active;
}

void DezaktywacjaKarty::apply(BaseCard* parent){
    parent->getActiveState() = false;
}
