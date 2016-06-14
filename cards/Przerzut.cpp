#include "cards/Przerzut.hpp"

using namespace Cards;

string Przerzut::getName(){
    return "przerzut";
}

bool Przerzut::canBePlayedAt(CardPtr card){
    shared_ptr<Targetable> targetable = dynamic_pointer_cast<Targetable>(card);
    if(targetable == nullptr) return false; //card is not Targetable so you cannot defend against it
    if(to == targetable->from) return false;//cannot use Przerzut as Odbicie
    if(getPriority()>targetable->getPriority()) return false;//TODO priority checking should be moved somewhere
    //TODO may need to check some locks
    return true;
}

CardPtr Przerzut::makeNew(){
    return make_shared<Przerzut>();
}

vector<CardPtr>& Przerzut::getAppliedCards(){
    return appliedCards;
}

int& Przerzut::getCUID(){
    return cuid;
}

bool& Przerzut::getActiveState(){
    return active;
}

void Przerzut::apply(BaseCard* parent){
    Targetable* tgt = dynamic_cast<Targetable*>(parent);
    if(tgt!=nullptr){
        tgt->to = to;
        tgt->from = from;
    }
}