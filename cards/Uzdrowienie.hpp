#ifndef UZDROWIENIE_HPP
#define UZDROWIENIE_HPP

#include "cards/Playable.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/Targetable.hpp"

namespace Cards{
class Uzdrowienie : public Playable, public Enhanceable, public Targetable{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getCUID() override;
    bool& getActiveState() override;

    void prepare() override;
    void played(GameServer& game) override;

    inline virtual ~Uzdrowienie(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
};
}

#endif

