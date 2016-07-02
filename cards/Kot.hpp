#ifndef KOT_HPP
#define KOT_HPP

#include "cards/Feature.hpp"
#include "cards/BaseCardImpl.hpp"
#include "cards/Enhanceable.hpp"

namespace Cards{
class Kot : public Feature, public Enhanceable, public BaseCardImpl{
public:
    string getName() override;
    CardPtr makeNew() override;


    void reset() override;
    void apply(GameServer::Player&) override;
    void afterEquip(GameServer::Player& player, GameServer& game) override;

    inline virtual ~Kot(){}
};
}

#endif
