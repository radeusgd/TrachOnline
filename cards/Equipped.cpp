#include "cards/Equipped.hpp"
#include "GameServer.hpp"

using namespace Cards;


bool Equipped::canBePlayedAt(CardPtr card, GameServer* game){
    if(card != nullptr) return false;
    return true;
}
 
