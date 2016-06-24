#ifndef ODBICIE_HPP
#define ODBICIE_HPP

#include "cards/Prioritized.hpp"
#include "cards/Modification.hpp"

namespace Cards{
class Odbicie : public virtual Prioritized, public virtual Modification{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
	int& getCUID() override;
    bool& getActiveState() override;
    
    int& getPriority() override;

    void apply(BaseCard* parent) override;

    inline virtual ~Odbicie(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
	int ownerid=-1;
    int priority;
};
}

#endif

