#ifndef CHWILASMIERCI_HPP
#define CHWILASMIERCI_HPP

#include "cards/Playable.hpp"

namespace Cards{
class ChwilaSmierci : public Playable{ //TODO maybe enhanceable
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;
    void played(GameServer& game) override;

    inline virtual ~ChwilaSmierci(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif
