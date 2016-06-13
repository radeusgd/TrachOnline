#ifndef BASECARD_HPP
#define BASECARD_HPP

#include <string>
#include <memory>
#include <vector>
#include "json.hpp"
using namespace std;

namespace Cards{
class BaseCard;
typedef shared_ptr<BaseCard> CardPtr;

class BaseCard{
public:
    /** returns the name of the card (used for image filename and identification) */
    virtual string getName()=0;
   
    /** whether this card can be played to modify another card (should infer from type or name)
     *      special case: nullptr - if the card can be played as a standalone action */
    virtual bool canBePlayedAt(CardPtr card)=0;

    /** creates a new card instance of the same type (used in calculations etc.) */
    virtual CardPtr makeNew()=0;
    
    /** List of cards that have been played on this one */
    virtual vector<CardPtr>& getAppliedCards()=0;

    /** Returns the unique id of the card on the table */
    virtual int& getCUID()=0;

    virtual nlohmann::json jsonify();
    
    inline virtual ~BaseCard(){}
};

}

using Cards::CardPtr;
#endif
