#ifndef KRADZIEZKARTY_HPP
#define KRADZIEZKARTY_HPP

#include "cards/Playable.hpp"
#include "cards/Targetable.hpp"

namespace Cards{
class KradziezKarty : public Playable, public Targetable{
public:
    string getName() override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
    int& getCUID() override;
    bool& getActiveState() override;

    void reset() override;

    void played(GameServer& game) override;

    inline virtual ~KradziezKarty(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};
}

#endif

