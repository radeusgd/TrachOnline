#ifndef BASECARDIMPL_HPP
#define BASECARDIMPL_HPP

#include "cards/BaseCard.hpp"

namespace Cards{
class BaseCardImpl : public virtual BaseCard{
public:
    vector<CardPtr>& getAppliedCards() override;
    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;

    inline virtual ~BaseCardImpl(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif

