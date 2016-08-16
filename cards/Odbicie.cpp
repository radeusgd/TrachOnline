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
        //swap(tgt->from,tgt->to);
        int tmp = tgt->to.playerId;
        tgt->to = Target(tgt->from,-1);
        tgt->from = tmp;
    }
}
