#include "cards/Recykling.hpp"

using namespace Cards;

string Recykling::getName(){
    return "recykling";
}

bool Recykling::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr Recykling::makeNew(){
    return make_shared<Recykling>();
}

void Recykling::played(GameServer& game){
  for(int i=0;i<value;i++){
    
  }
}
