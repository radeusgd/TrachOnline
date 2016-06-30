#ifndef MALALAPKA_HPP
#define MALALAPKA_HPP

#include "cards/Feature.hpp"
#include "cards/BaseCardImpl.hpp"
#include "cards/Enhanceable.hpp"

namespace Cards{
class MalaLapka : public Feature, public Enhanceable, public BaseCardImpl{
public:
    string getName() override;
    CardPtr makeNew() override;

    void reset() override;
    void apply(GameServer::Player&) override;

    inline virtual ~MalaLapka(){}
};
}

#endif

