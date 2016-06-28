#ifndef ODWROCENIECZASU_HPP
#define ODWROCENIECZASU_HPP

#include "cards/Playable.hpp"

namespace Cards{
class OdwrocenieCzasu : public Playable{
public:
    string getName() override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;

    void played(GameServer& game) override;

    inline virtual ~OdwrocenieCzasu(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif

