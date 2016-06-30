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

void DezaktywacjaKarty::apply(BaseCard* parent){
    parent->getActiveState() = false;
}
