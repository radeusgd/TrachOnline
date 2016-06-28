#ifndef WAMPIR_HPP
#define WAMPIR_HPP

#include "cards/Feature.hpp"

namespace Cards{
class Wampir : public Feature{
public:
    string getName() override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;

    void apply(GameServer::Player&) override;

    inline virtual ~Wampir(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif
