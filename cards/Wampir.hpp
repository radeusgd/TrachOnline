#ifndef WAMPIR_HPP
#define WAMPIR_HPP

#include "cards/Feature.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class Wampir : public Feature, public BaseCardImpl{
public:
    string getName() override;
    CardPtr makeNew() override;

    void apply(GameServer::Player&) override;

    inline virtual ~Wampir(){}
};
}

#endif
