#ifndef CHWILASMIERCI_HPP
#define CHWILASMIERCI_HPP

#include "cards/Playable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class ChwilaSmierci : public Playable, public BaseCardImpl{ //TODO maybe enhanceable
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;
    
    void played(GameServer& game) override;

    inline virtual ~ChwilaSmierci(){}
};
}

#endif
