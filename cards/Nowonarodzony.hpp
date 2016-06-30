#ifndef NOWONARODZONY_HPP
#define NOWONARODZONY_HPP

#include "cards/Playable.hpp"
#include "cards/BaseCardImpl.hpp"
#include "cards/Targetable.hpp"

namespace Cards{
class Nowonarodzony : public Playable, public Targetable, public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;

    
    void played(GameServer& game) override;

    inline virtual ~Nowonarodzony(){}
};
}

#endif

