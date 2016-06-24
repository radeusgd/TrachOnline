#ifndef ZMASOWANYATAK_HPP
#define ZMASOWANYATAK_HPP

#include "cards/Playable.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/Prioritized.hpp"

namespace Cards{
class ZmasowanyAtak : public Playable, public Enhanceable, public Prioritized{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getOwnerId() override;
	int& getCUID() override;
    bool& getActiveState() override;
    
    void reset() override;
    int& getPriority() override;
    void refresh(GameServer& game) override;
    void played(GameServer& game) override;

    nlohmann::json jsonify() override;

    inline virtual ~ZmasowanyAtak(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    int priority;
	int ownerid=-1;
    bool childrenPrepared=false;
    void prepareChildren(GameServer& game);
};
}

#endif

