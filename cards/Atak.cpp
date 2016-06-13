#include "cards/Atak.hpp"
#include "GameServer.hpp"

using namespace Cards;

Atak::Atak(){
    value = 1;
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

void Atak::played(GameServer& game){
   cout<<from<<" atakuje "<<to<<endl;
   //TODO check things??
    game.players[to].HP-=value;
}
