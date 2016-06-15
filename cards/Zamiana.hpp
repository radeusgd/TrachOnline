#ifndef ZAMIANA_HPP
#define ZAMIANA_HPP

#include "cards/Playable.hpp"
#include "cards/Targetable.hpp"

namespace Cards{
class Zamiana : public Playable, public Targetable{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getCUID() override;
    bool& getActiveState() override;
    
    void played(GameServer& game) override;

    inline virtual ~Zamiana(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
};
}

#endif

