#ifndef ATAK_HPP
#define ATAK_HPP

#include "cards/Playable.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/Targetable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{

class Atak : public Playable, public Enhanceable, public Targetable, public BaseCardImpl {
public:
    Atak();
    string getName() override;
    bool canBeTargetedAt(Target t) override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;
    void reset() override;
    void played(GameServer& game) override;

    inline virtual ~Atak(){}
};

}
#endif /* ATAK_HPP */
