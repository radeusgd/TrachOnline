#include "cards/Playable.hpp"

using namespace Cards;

bool Playable::canBePlayedAt(CardPtr card, GameServer* game){
    return (card == nullptr);
}
