#include "cards/Atak.hpp"
#include "GameServer.hpp"

using namespace Cards;

Atak::Atak(){
    reset();
}

string Atak::getName(){
    return "atak";
}

bool Atak::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;//TODO kontratak
    return false;
}

CardPtr Atak::makeNew(){
    return make_shared<Atak>();
}

void Atak::reset(){
    Targetable::reset();
    priority = 6;
    value=1;
    active=true;
}

void Atak::played(GameServer& game){
    //cout<<from<<" atakuje "<<to<<endl;
    int damage = game.players[from].giveDamage(value);
    int takenDamage = game.handleTargetReceiveDamage(to,value);//game.players[to].receiveDamage(damage);
    game.players[from].givenDamage(takenDamage);
}
