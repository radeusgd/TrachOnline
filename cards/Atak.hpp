#ifndef ATAK_HPP
#define ATAK_HPP

#include "cards/Playable.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/Targetable.hpp"

namespace Cards{

class Atak : public Playable, public Enhanceable, public Targetable { 
public:
    Atak();
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
	int& getCUID() override;
    bool& getActiveState() override;
    
    void reset() override;
    void played(GameServer& game) override;

    inline virtual ~Atak(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int ownerid=-1;
};

}
#endif /* ATAK_HPP */
