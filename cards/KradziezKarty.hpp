#ifndef KRADZIEZKARTY_HPP
#define KRADZIEZKARTY_HPP

#include "cards/Playable.hpp"
#include "cards/BaseCardImpl.hpp"
#include "cards/Targetable.hpp"

namespace Cards{
class KradziezKarty : public Playable, public Targetable, public BaseCardImpl{
public:
    string getName() override;
    CardPtr makeNew() override;

    void reset() override;

    void played(GameServer& game) override;

    inline virtual ~KradziezKarty(){}
};
}

#endif

