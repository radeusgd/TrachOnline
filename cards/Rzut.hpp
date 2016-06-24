#ifndef RZUT_HPP
#define RZUT_HPP

#include "cards/Playable.hpp"
#include "cards/Targetable.hpp"

namespace Cards{
class Rzut : public Playable, public Targetable{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
	int& getCUID() override;
    bool& getActiveState() override;

    void played(GameServer& game) override;

    inline virtual ~Rzut(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
	int ownerid=-1;
};
}

#endif

