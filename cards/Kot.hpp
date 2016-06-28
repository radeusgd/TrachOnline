#ifndef KOT_HPP
#define KOT_HPP

#include "cards/Feature.hpp"
#include "cards/Enhanceable.hpp"

namespace Cards{
class Kot : public Feature, public Enhanceable{
public:
    string getName() override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;

    void reset() override;
    void apply(GameServer::Player&) override;
    void afterEquip(GameServer::Player& player, GameServer& game) override;

    inline virtual ~Kot(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif
