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

    int& getCUID() override;

    void played() override;

    inline virtual ~Atak(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
};

}
#endif /* ATAK_HPP */
