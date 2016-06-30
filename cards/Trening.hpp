#ifndef TRENING_HPP
#define TRENING_HPP

#include "cards/Feature.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class Trening : public Feature, public Enhanceable, public BaseCardImpl{
public:
    string getName() override;
    CardPtr makeNew() override;

    
    void reset() override;
    void apply(GameServer::Player&) override;
    void afterEquip(GameServer::Player& player, GameServer& game) override;

    inline virtual ~Trening(){}
};
}

#endif

