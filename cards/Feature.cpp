#include "cards/Feature.hpp"

using namespace Cards;

void Feature::reset(){
    Targetable::reset();
    priority = 4;
}
