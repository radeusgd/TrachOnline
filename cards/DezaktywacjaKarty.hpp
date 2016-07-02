#ifndef DEZAKTYWACJAKARTY_HPP
#define DEZAKTYWACJAKARTY_HPP

#include "cards/Modification.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class DezaktywacjaKarty : public Modification, public BaseCardImpl{//FIXME should also be Playable to deactivate static cards
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;

    void apply(BaseCard* parent) override;

    inline virtual ~DezaktywacjaKarty(){}
};
}

#endif

