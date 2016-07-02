#ifndef WIELKALAPA_HPP
#define WIELKALAPA_HPP

#include "cards/Feature.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/BaseCardImpl.hpp"

namespace Cards{
class WielkaLapa : public Feature, public Enhanceable, public BaseCardImpl{
public:
    string getName() override;
    CardPtr makeNew() override;


    void reset() override;
    void apply(GameServer::Player&) override;

    inline virtual ~WielkaLapa(){}
};
}

#endif
