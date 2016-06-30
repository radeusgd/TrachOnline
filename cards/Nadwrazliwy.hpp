#ifndef NADWRAZLIWY_HPP
#define NADWRAZLIWY_HPP

#include "cards/Feature.hpp"
#include "cards/BaseCardImpl.hpp"
#include "cards/Enhanceable.hpp"

namespace Cards{
class Nadwrazliwy : public Feature, public Enhanceable, public BaseCardImpl{
public:
    string getName() override;
    CardPtr makeNew() override;

    void reset() override;
    void apply(GameServer::Player&) override;

    inline virtual ~Nadwrazliwy(){}
};
}

#endif

