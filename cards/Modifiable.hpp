#ifndef MODIFIABLE_HPP
#define MODIFIABLE_HPP

#include "cards/BaseCard.hpp"

namespace Cards{
class Modifiable : public virtual BaseCard{
public:
    /*
     * prepares base values for this card, run before paying or computing preview
     * */
    virtual void prepare()=0;

    /*
     * updates cards values based on children
     * */
    virtual void refresh();

    /*
     * applies children's changes
     * (ref. implementation, can be changed by inherited classes)
     * */
    virtual void applyChildren();

    inline virtual ~Modifiable(){}
};
}

#endif

