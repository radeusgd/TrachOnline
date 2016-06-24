#ifndef #NAME#_HPP
#define #NAME#_HPP

#include "cards/BaseCard.hpp"

namespace Cards{
class #Name# : public BaseCard{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;

    inline virtual ~#Name#(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif
