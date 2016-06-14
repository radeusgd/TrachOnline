#include "cards/Atak.hpp"
#include "GameServer.hpp"

using namespace Cards;

Atak::Atak(){
    prepare();
}

string Atak::getName(){
    return "atak";
}

bool Atak::canBePlayedAt(CardPtr card){
    if(card==nullptr) return true;//TODO kontratak
    return false;
}

CardPtr Atak::makeNew(){
    return make_shared<Atak>();
}

vector<CardPtr>& Atak::getAppliedCards(){
    return appliedCards;
}

int& Atak::getCUID(){
    return cuid;
}

bool& Atak::getActiveState(){
    return active;
}

void Atak::prepare(){
    value=1;
}

void Atak::played(GameServer& game){
    //cout<<from<<" atakuje "<<to<<endl;
    game.players[to].dealDamage(value);
}
