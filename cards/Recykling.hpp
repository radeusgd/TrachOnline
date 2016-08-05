#ifndef RECYKLING_HPP
#define RECYKLING_HPP

#include "cards/BaseCardImpl.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/Playable.hpp"

namespace Cards{
class Recykling : public BaseCardImpl, public Enhanceable, public Playable{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;
    void played(GameServer& game) override;
    inline virtual ~Recykling(){}
};
}

#endif
