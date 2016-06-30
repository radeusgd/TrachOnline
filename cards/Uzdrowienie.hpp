#ifndef UZDROWIENIE_HPP
#define UZDROWIENIE_HPP

#include "cards/Playable.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/Targetable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class Uzdrowienie : public Playable, public Enhanceable, public Targetable, public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;

    void reset() override;
    void played(GameServer& game) override;

    inline virtual ~Uzdrowienie(){}
};
}

#endif

