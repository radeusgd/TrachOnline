#ifndef OSLABIENIE_HPP
#define OSLABIENIE_HPP

#include "cards/Feature.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class Oslabienie : public Feature, public Enhanceable, public BaseCardImpl{
public:
    string getName() override;
    CardPtr makeNew() override;


    void reset() override;
    void apply(GameServer::Player&) override;
    void beforeEquip(GameServer::Player& player, GameServer& game) override;

    inline virtual ~Oslabienie(){}
};
}

#endif
