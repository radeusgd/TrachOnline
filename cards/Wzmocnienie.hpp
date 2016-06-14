#ifndef WZMOCNIENIE_HPP
#define WZMOCNIENIE_HPP

#include "cards/Modification.hpp"

namespace Cards{
class Wzmocnienie : public Modification{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getCUID() override;
    bool& getActiveState() override;

    void apply(BaseCard* parent) override;

    inline virtual ~Wzmocnienie(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
};
}

#endif

