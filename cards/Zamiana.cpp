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

void Zamiana::played(GameServer& game){
    int to = Zamiana::to.playerId;//TODO get rid of shadowing
    swap(game.players[to],game.players[from]);//swap player data
    swap(game.players[to].ws,game.players[from].ws);//swap WS handles back to original places
    swap(game.players[to].id,game.players[from].id);
    game.updateCards(game.players[to]);
    game.updateCards(game.players[from]);
}

bool Zamiana::canBeTargetedAt(Target t){
  if(t.cardId==-1) return true;
  return false;
}
