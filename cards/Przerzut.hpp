#ifndef PRZERZUT_HPP
#define PRZERZUT_HPP

#include "cards/Modification.hpp"
#include "cards/Targetable.hpp"

namespace Cards{
class Przerzut : public Modification, public Targetable {
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
	int& getCUID() override;
    bool& getActiveState() override;

    void apply(BaseCard* parent) override;

    inline virtual ~Przerzut(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
	int ownerid=-1;
};
}

#endif

