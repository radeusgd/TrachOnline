#include "cards/Feature.hpp"

using namespace Cards;

void Feature::reset(){
    Targetable::reset();
    priority = 4;
}

bool Feature::canBeTargetedAt(Target t){
  if(t.cardId==-1) return true;
  return false;
}
