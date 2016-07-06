#ifndef REGENERUJACYSIE_HPP
#define REGENERUJACYSIE_HPP

#include "cards/TurnBased.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/BaseCardImpl.hpp"
#include "cards/Feature.hpp"

namespace Cards{
class RegenerujacySie : public TurnBased, public Enhanceable, public Feature, public BaseCardImpl{
public:
    string getName() override;
    CardPtr makeNew() override;

    void reset() override;
    void apply(GameServer::Player& player) override;
    void execute(GameServer& game, GameServer::Player& p) override;

    inline virtual ~RegenerujacySie(){}
};
}

#endif
