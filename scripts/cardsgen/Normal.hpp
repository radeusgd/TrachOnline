#ifndef #NAME#_HPP
#define #NAME#_HPP

#include "cards/BaseCardImpl.hpp"

namespace Cards{
class #Name# : public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;

    inline virtual ~#Name#(){}
};
}

#endif
