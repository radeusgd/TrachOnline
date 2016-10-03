#ifndef PELNAREGENERACJA_HPP
#define PELNAREGENERACJA_HPP

#include "cards/Playable.hpp"
#include "cards/BaseCardImpl.hpp"
#include "cards/Targetable.hpp"

namespace Cards{
class PelnaRegeneracja : public Playable, public Targetable, public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;


    void reset() override;
    void played(GameServer& game) override;

    bool canBeTargetedAt(Target t) override;

    inline virtual ~PelnaRegeneracja(){}
};
}

#endif
