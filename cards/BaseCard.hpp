#ifndef BASECARD_HPP
#define BASECARD_HPP

#include <string>
#include <memory>
#include <vector>
#include "json.hpp"
using namespace std;

class GameServer;
namespace Cards{
class BaseCard;
typedef shared_ptr<BaseCard> CardPtr;

class BaseCard{
public:
    /** returns the name of the card (used for image filename and identification) */
    virtual string getName()=0;
   
    /** whether this card can be played to modify another card (should infer from type or name)
     *      special case: nullptr - if the card can be played as a standalone action */
    virtual bool canBePlayedAt(CardPtr card, GameServer* game)=0;

    /** creates a new card instance of the same type (used in calculations etc.) */
    virtual CardPtr makeNew()=0;
    
    /** List of cards that have been played on this one */
    virtual vector<CardPtr>& getAppliedCards()=0;

    /** Returns id of current card owner */
    virtual int& getOwnerId()=0;

    /** Returns the unique id of the card on the table */
    virtual int& getCUID()=0;

    /*
     * run after a card has been attached, card params (like priority) could have changed so they should be recomputed
     */
    inline virtual void reset(){
        getActiveState() = true;
    }

    /*
     * run after a card has been attached, card params (like priority) could have changed so they should be recomputed
     */
    virtual void refresh(GameServer& serv);

    /*
     * applies children's changes
     * (ref. implementation, can be changed by inherited classes)
     * */
    virtual void applyChildren(GameServer& game);

    /*
     * used to potentially deactivate card
     */
    virtual bool& getActiveState()=0;

    virtual nlohmann::json jsonify();
    
    inline virtual ~BaseCard(){}
};

}

using Cards::CardPtr;
#endif
