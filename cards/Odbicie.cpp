#include "cards/Odbicie.hpp"
#include "cards/Targetable.hpp"

using namespace Cards;

string Odbicie::getName(){
    return "odbicie";
}

bool Odbicie::canBePlayedAt(CardPtr card, GameServer* game){
    if(card->getName() == "przerzut") return false;
    shared_ptr<Targetable> targetable = dynamic_pointer_cast<Targetable>(card);
    if(targetable == nullptr) return false; //card is not Targetable so you cannot defend against it
    if(getPriority()>targetable->getPriority()) return false;//TODO priority checking should be moved somewhere
    //TODO may need to check some locks
    return true;
}

CardPtr Odbicie::makeNew(){
    return make_shared<Odbicie>();
}

vector<CardPtr>& Odbicie::getAppliedCards(){
    return appliedCards;
}

int& Odbicie::getOwnerId(){
    return ownerid;
}
int& Odbicie::getCUID(){
    return cuid;
}

bool& Odbicie::getActiveState(){
    return active;
}

int& Odbicie::getPriority(){
    return priority;
}

void Odbicie::reset(){
    BaseCard::reset();
    priority = 5;
}

void Odbicie::apply(BaseCard* parent){
    Targetable* tgt = dynamic_cast<Targetable*>(parent);
    if(tgt!=nullptr){
        swap(tgt->from,tgt->to);
    }
}
