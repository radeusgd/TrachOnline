#ifndef #NAME#_HPP
#define #NAME#_HPP

#include "cards/BaseCard.hpp"

namespace Cards{
class #Name# : public BaseCard{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getCUID() override;

    inline virtual ~#Name#(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
};
}

#endif