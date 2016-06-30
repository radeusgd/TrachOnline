#ifndef NIETYKALNY_HPP
#define NIETYKALNY_HPP

#include "cards/Prioritized.hpp"
#include "cards/BaseCardImpl.hpp"
#include "cards/Modification.hpp"

namespace Cards{
class Nietykalny : public virtual Prioritized, public virtual Modification, public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;


    int& getPriority() override;
    void reset() override;

    void apply(BaseCard* parent) override;

    inline virtual ~Nietykalny(){}
protected:
    int priority;
};
}

#endif
