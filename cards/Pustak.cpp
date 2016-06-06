#include "cards/Pustak.hpp"

string Pustak::getName(){
    return "pustak";
}

bool Pustak::canBePlayedAt(BaseCard* card){
    if(card==nullptr) return true;
    return false;
}
