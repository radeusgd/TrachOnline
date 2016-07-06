#include "cards/RegenerujacySie.hpp"

using namespace Cards;

string RegenerujacySie::getName(){
    return "regenerujacy_sie";
}

CardPtr RegenerujacySie::makeNew(){
    return make_shared<RegenerujacySie>();
}

void RegenerujacySie::reset(){
    Feature::reset();
    value = 1;
}

void RegenerujacySie::apply(GameServer::Player& player){
  return;
}

void RegenerujacySie::execute(GameServer& game, GameServer::Player& p){
  p.HP+=value;
  p.clampHP();
}
