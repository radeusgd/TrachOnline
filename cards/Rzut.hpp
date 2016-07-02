#ifndef RZUT_HPP
#define RZUT_HPP

#include "cards/Playable.hpp"
#include "cards/Targetable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class Rzut : public Playable, public Targetable, public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;


    void played(GameServer& game) override;

    inline virtual ~Rzut(){}
};
}

#endif

