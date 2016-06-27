#include "cards/Equipped.hpp"

using namespace Cards;


bool Equipped::canBePlayedAt(CardPtr card, GameServer* game){
    if(card != nullptr) return false;
    return true;
}
