#ifndef BASECARD_HPP
#define BASECARD_HPP

#include <string>
using namespace std;

class BaseCard{
public:
    /** returns the name of the card (used for image filename and identification) */
    virtual string getName()=0;
   
    /** whether this card can be played to modify another card (should infer from type or name)
     *      special case: nullptr - if the card can be played as a standalone action */
    virtual bool canBePlayedAt(BaseCard* card)=0;
    
    inline virtual ~BaseCard(){}
};

#endif
