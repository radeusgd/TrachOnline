#ifndef WYMIANAKART_HPP
#define WYMIANAKART_HPP

#include "cards/Playable.hpp"
#include "cards/Targetable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class WymianaKart : public Playable, public Targetable, public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;


    void played(GameServer& game) override;

    inline virtual ~WymianaKart(){}
};
}

#endif

