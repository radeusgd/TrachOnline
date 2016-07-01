#ifndef PODNIESIENIEPRIORYTETU_HPP
#define PODNIESIENIEPRIORYTETU_HPP

#include "cards/Modification.hpp"
#include "cards/Enhanceable.hpp"

namespace Cards{
class PodniesieniePriorytetu : public Modification, public Enhanceable{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
	int& getCUID() override;
    bool& getActiveState() override;

    void apply(BaseCard* parent) override;
    void reset() override;

    inline virtual ~PodniesieniePriorytetu(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
	int ownerid=-1;
};
}

#endif
