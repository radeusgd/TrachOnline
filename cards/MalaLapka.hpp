#ifndef MALALAPKA_HPP
#define MALALAPKA_HPP

#include "cards/Feature.hpp"
#include "cards/Enhanceable.hpp"

namespace Cards{
class MalaLapka : public Feature, public Enhanceable{
public:
    string getName() override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;
    
    void reset() override;
    void apply(GameServer::Player&) override;

    inline virtual ~MalaLapka(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif

