#ifndef PODNIESIENIEPRIORYTETU_HPP
#define PODNIESIENIEPRIORYTETU_HPP

#include "cards/Modification.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class PodniesieniePriorytetu : public Modification, public Enhanceable, public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;

    void apply(BaseCard* parent) override;
    void reset() override;

    inline virtual ~PodniesieniePriorytetu(){}
};
}

#endif
