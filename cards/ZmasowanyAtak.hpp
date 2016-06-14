#ifndef ZMASOWANYATAK_HPP
#define ZMASOWANYATAK_HPP

#include "cards/Atak.hpp"

namespace Cards{
class ZmasowanyAtak : public Atak{
public:
    string getName() override;
    bool canBePlayedAt(CardPtr card) override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getCUID() override;
    bool& getActiveState() override;
    
    void prepare() override;
    void refresh(GameServer& game) override;
    void played(GameServer& game) override;

    nlohmann::json jsonify() override;

    inline virtual ~ZmasowanyAtak(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
    bool childrenPrepared=false;
    void prepareChildren(GameServer& game);
};
}

#endif

