#include "cards/Nietykalny.hpp"
#include "cards/Targetable.hpp"

using namespace Cards;

string Nietykalny::getName(){
    return "nietykalny";
}

bool Nietykalny::canBePlayedAt(CardPtr card, GameServer* game){
    shared_ptr<Targetable> targetable = dynamic_pointer_cast<Targetable>(card);
    if(targetable == nullptr) return false; //card is not Targetable so you cannot defend against it
//    cout<<getPriority()<<" vs "<<targetable->getPriority()<<endl;
    if(getPriority()>targetable->getPriority()) return false;//TODO priority checking should be moved somewhere
    //TODO may need to check some locks
    return true;
}

CardPtr Nietykalny::makeNew(){
    return make_shared<Nietykalny>();
}

void Nietykalny::reset(){
    BaseCard::reset();
    priority = 1;
}

int& Nietykalny::getPriority(){
    return priority;
}

void Nietykalny::apply(BaseCard* parent){
    parent->getActiveState() = false;
}
