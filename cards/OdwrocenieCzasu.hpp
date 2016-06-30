#ifndef ODWROCENIECZASU_HPP
#define ODWROCENIECZASU_HPP

#include "cards/Playable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class OdwrocenieCzasu : public Playable, public BaseCardImpl{
public:
    string getName() override;
    CardPtr makeNew() override;

    void played(GameServer& game) override;

    inline virtual ~OdwrocenieCzasu(){}
};
}

#endif

