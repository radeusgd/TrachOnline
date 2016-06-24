#include "cards/Wzmocnienie.hpp"
#include "cards/Enhanceable.hpp"

using namespace Cards;

string Wzmocnienie::getName(){
    return "wzmocnienie";
}

bool Wzmocnienie::canBePlayedAt(CardPtr card){
    shared_ptr<Enhanceable> enhanceable = dynamic_pointer_cast<Enhanceable>(card);
    if(enhanceable==nullptr) return false;
    if(getOwnerId()!=card->getOwnerId()) return false;
    return true;
}

CardPtr Wzmocnienie::makeNew(){
    return make_shared<Wzmocnienie>();
}

vector<CardPtr>& Wzmocnienie::getAppliedCards(){
    return appliedCards;
}

int& Wzmocnienie::getOwnerId(){
    return ownerid;
}
int& Wzmocnienie::getCUID(){
    return cuid;
}

bool& Wzmocnienie::getActiveState(){
    return active;
}

void Wzmocnienie::apply(BaseCard* parent){
    Enhanceable* enhanceable = dynamic_cast<Enhanceable*>(parent);
    if(enhanceable!=nullptr){
        enhanceable->value+=this->value;
    }
}

void Wzmocnienie::reset(){
    BaseCard::reset();
    value = 1;
}
