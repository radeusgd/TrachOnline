#ifndef WYROWNANIESZANS_HPP
#define WYROWNANIESZANS_HPP

#include "cards/Playable.hpp"

namespace Cards{
class WyrownanieSzans : public Playable{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;

    void played(GameServer& game) override;
    inline virtual ~WyrownanieSzans(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif
