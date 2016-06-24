#include "cards/Zamiana.hpp"
#include "GameServer.hpp"

using namespace Cards;

string Zamiana::getName(){
    return "zamiana";
}

bool Zamiana::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr Zamiana::makeNew(){
    return make_shared<Zamiana>();
}

vector<CardPtr>& Zamiana::getAppliedCards(){
    return appliedCards;
}

int& Zamiana::getOwnerId(){
    return ownerid;
}
int& Zamiana::getCUID(){
    return cuid;
}

bool& Zamiana::getActiveState(){
    return active;
}

void Zamiana::played(GameServer& game){
    swap(game.players[to],game.players[from]);//swap player data
    swap(game.players[to].ws,game.players[from].ws);//swap WS handles back to original places
    game.updateCards(game.players[to]);
    game.updateCards(game.players[from]);
}
