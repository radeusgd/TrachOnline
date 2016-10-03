#include "cards/Nowonarodzony.hpp"
#include "GameServer.hpp"
using namespace Cards;

string Nowonarodzony::getName(){
    return "nowonarodzony";
}

bool Nowonarodzony::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr Nowonarodzony::makeNew(){
    return make_shared<Nowonarodzony>();
}

void Nowonarodzony::played(GameServer& game){
    int to = Nowonarodzony::to.playerId;//TODO may consider adding some checks and fixing name shadowing
    game.players[to].prepare();
    for(auto c : game.players[to].hand) game.recycleCard(c);
    game.players[to].hand.clear();
    for(auto c : game.players[to].equipment) game.recycleCard(c);
    game.players[to].equipment.clear();
    game.players[to].HP = game.players[to].maxHP;
    game.fillCards(game.players[to]);
}

bool Nowonarodzony::canBeTargetedAt(Target t){
  if(t.cardId==-1) return true;
  return false;
}
