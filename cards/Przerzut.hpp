#ifndef PRZERZUT_HPP
#define PRZERZUT_HPP

#include "cards/Modification.hpp"
#include "cards/Targetable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class Przerzut : public Modification, public Targetable , public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;


    void reset() override;
    void apply(BaseCard* parent) override;

    bool canBeTargetedAt(Target t) override;

    inline virtual ~Przerzut(){}
};
}

#endif
