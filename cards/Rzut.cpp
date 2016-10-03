#include "cards/Rzut.hpp"
#include "GameServer.hpp"

using namespace Cards;

string Rzut::getName(){
    return "rzut";
}

bool Rzut::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr Rzut::makeNew(){
    return make_shared<Rzut>();
}

void Rzut::played(GameServer& game){
  Message m;
  m.name = "rzucasz";
  game.send(game.players[from].ws, m);
  game.beginDialogue();
}

bool Rzut::canBeTargetedAt(Target t){
  if(t.cardId==-1) return true;
  return false;
}
