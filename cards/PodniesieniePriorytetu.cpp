#include "cards/PodniesieniePriorytetu.hpp"
#include "cards/Prioritized.hpp"

using namespace Cards;

string PodniesieniePriorytetu::getName(){
    return "podniesienie_priorytetu";
}

bool PodniesieniePriorytetu::canBePlayedAt(CardPtr card, GameServer* game){
    shared_ptr<Prioritized> prioritized = dynamic_pointer_cast<Prioritized>(card);
    if(prioritized==nullptr) return false;
    if(getOwnerId()!=card->getOwnerId()) return false;
    if(prioritized->getPriority()<2) return false;
    return true;
}

CardPtr PodniesieniePriorytetu::makeNew(){
    return make_shared<PodniesieniePriorytetu>();
}

vector<CardPtr>& PodniesieniePriorytetu::getAppliedCards(){
    return appliedCards;
}

int& PodniesieniePriorytetu::getOwnerId(){
    return ownerid;
}
int& PodniesieniePriorytetu::getCUID(){
    return cuid;
}

bool& PodniesieniePriorytetu::getActiveState(){
    return active;
}

void PodniesieniePriorytetu::apply(BaseCard* parent){
    Prioritized* prioritized = dynamic_cast<Prioritized*>(parent);
    if(prioritized!=nullptr){
        prioritized->getPriority()-=this->value;
    }
}

void PodniesieniePriorytetu::reset(){
    BaseCard::reset();
    value = 2;
}
