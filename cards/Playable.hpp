#ifndef PLAYABLE_HPP
#define PLAYABLE_HPP 

#include "cards/BaseCard.hpp"
class GameServer;
namespace Cards{
class Playable : public virtual BaseCard{
public:
    /** called after the card has been played and its action shall execute
     *
     * for action cards (like attack) it should execute the action now
     * for table cards (like an item or a trait) it should place itself into players inventory
     * */
    virtual void played(GameServer& game)=0;
    /*
     * prepares base values for this card, run before paying or computing preview
     * */
    virtual void prepare()=0;

    bool canBePlayedAt(CardPtr card) override;

    inline virtual ~Playable(){}
};
}

#endif /* PLAYABLE_HPP */
