#include "cards/Przerzut.hpp"
#include "GameServer.hpp"

using namespace Cards;

string Przerzut::getName(){
    return "przerzut";
}

bool Przerzut::canBePlayedAt(CardPtr card, GameServer* game){
    shared_ptr<Targetable> targetable = dynamic_pointer_cast<Targetable>(card);
    if(targetable == nullptr) return false; //card is not Targetable so you cannot defend against it
    if(to.cardId == -1 && to.playerId == targetable->from && game->livingPlayersCount()>2) return false;//cannot use Przerzut as Odbicie unless there are only 2 players playing
    if(getPriority()>targetable->getPriority()) return false;
    //TODO may need to check some locks
    return true;
}

CardPtr Przerzut::makeNew(){
    return make_shared<Przerzut>();
}

void Przerzut::reset(){
    Targetable::reset();
    priority = 5;
}

void Przerzut::apply(BaseCard* parent){
    Targetable* tgt = dynamic_cast<Targetable*>(parent);
    if(tgt!=nullptr){
        tgt->to = to;
        tgt->from = from;
    }
}
