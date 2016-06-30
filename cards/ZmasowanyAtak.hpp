#ifndef ZMASOWANYATAK_HPP
#define ZMASOWANYATAK_HPP

#include "cards/Playable.hpp"
#include "cards/BaseCardImpl.hpp"
#include "cards/Enhanceable.hpp"
#include "cards/Prioritized.hpp"

namespace Cards{
class ZmasowanyAtak : public Playable, public Enhanceable, public Prioritized, public BaseCardImpl{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    CardPtr makeNew() override;
    
    void reset() override;
    int& getPriority() override;
    void refresh(GameServer& game) override;
    void played(GameServer& game) override;

    nlohmann::json jsonify() override;

    inline virtual ~ZmasowanyAtak(){}
protected:
	int priority;
    bool childrenPrepared=false;
    void prepareChildren(GameServer& game);
};
}

#endif

