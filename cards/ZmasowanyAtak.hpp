#ifndef ZMASOWANYATAK_HPP
#define ZMASOWANYATAK_HPP

#include "cards/Playable.hpp"
#include "cards/Enhanceable.hpp"

namespace Cards{
class ZmasowanyAtak : public Playable, public Enhanceable{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
	int& getCUID() override;
    bool& getActiveState() override;
    
    void reset() override;
    void refresh(GameServer& game) override;
    void played(GameServer& game) override;

    nlohmann::json jsonify() override;

    inline virtual ~ZmasowanyAtak(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
	int ownerid=-1;
    bool childrenPrepared=false;
    void prepareChildren(GameServer& game);
};
}

#endif

