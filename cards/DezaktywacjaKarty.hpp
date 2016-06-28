#ifndef DEZAKTYWACJAKARTY_HPP
#define DEZAKTYWACJAKARTY_HPP

#include "cards/Modification.hpp"

namespace Cards{
class DezaktywacjaKarty : public Modification{//FIXME should also be Playable to deactivate static cards
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;

    void apply(BaseCard* parent) override;

    inline virtual ~DezaktywacjaKarty(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif

