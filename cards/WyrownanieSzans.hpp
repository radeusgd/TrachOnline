#ifndef WYROWNANIESZANS_HPP
#define WYROWNANIESZANS_HPP

#include "cards/Playable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class WyrownanieSzans : public Playable, public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;


    void played(GameServer& game) override;
    inline virtual ~WyrownanieSzans(){}
};
}

#endif
