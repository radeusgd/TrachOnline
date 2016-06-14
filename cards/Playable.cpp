#include "cards/Playable.hpp"

using namespace Cards;

bool Playable::canBePlayedAt(CardPtr card){
    return (card == nullptr);
}
