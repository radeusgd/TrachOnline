#ifndef NIETYKALNY_HPP
#define NIETYKALNY_HPP

#include "cards/Prioritized.hpp"
#include "cards/Modification.hpp"

namespace Cards{
class Nietykalny : public virtual Prioritized, public virtual Modification{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
	int& getCUID() override;
    bool& getActiveState() override;

    int& getPriority() override;
    void reset() override;

    void apply(BaseCard* parent) override;

    inline virtual ~Nietykalny(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
	int ownerid=-1;
    int priority;
};
}

#endif