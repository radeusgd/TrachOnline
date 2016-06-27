#ifndef SUPERWYTRZYMALY_HPP
#define SUPERWYTRZYMALY_HPP

#include "cards/Feature.hpp"
#include "cards/Enhanceable.hpp"

namespace Cards{
class Superwytrzymaly : public Feature, public Enhanceable{
public:
    string getName() override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;

    void reset() override;
    void apply(GameServer::Player&) override;
    void equip(GameServer::Player& player, GameServer& game) override;

    inline virtual ~Superwytrzymaly(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif
