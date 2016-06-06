#include "cards/Pustak.hpp"

string Pustak::getName(){
    return "pustak";
}

bool Pustak::canBePlayedAt(shared_ptr<BaseCard> card){
    if(card==nullptr) return true;
    return false;
}

shared_ptr<BaseCard> Pustak::makeNew(){
    return make_shared<Pustak>();
}

void Pustak::played(){
    //does nothing
}
