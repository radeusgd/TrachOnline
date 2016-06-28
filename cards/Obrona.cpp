#include "cards/Obrona.hpp"
#include "cards/Targetable.hpp"

using namespace Cards;

string Obrona::getName(){
    return "obrona";
}

bool Obrona::canBePlayedAt(CardPtr card, GameServer* game){
    if(card->getName() == "przerzut") return false;
    shared_ptr<Targetable> targetable = dynamic_pointer_cast<Targetable>(card);
    if(targetable == nullptr) return false; //card is not Targetable so you cannot defend against it
//    cout<<getPriority()<<" vs "<<targetable->getPriority()<<endl;
    if(getPriority()>targetable->getPriority()) return false;//TODO priority checking should be moved somewhere
    //TODO may need to check some locks
    return true;
}

CardPtr Obrona::makeNew(){
    return make_shared<Obrona>();
}

vector<CardPtr>& Obrona::getAppliedCards(){
    return appliedCards;
}

void Obrona::reset(){
    BaseCard::reset();
    priority = 5;
}

int& Obrona::getOwnerId(){
    return ownerid;
}
int& Obrona::getCUID(){
    return cuid;
}

bool& Obrona::getActiveState(){
    return active;
}

int& Obrona::getPriority(){
    return priority;
}

void Obrona::apply(BaseCard* parent){
    parent->getActiveState() = false;
}
