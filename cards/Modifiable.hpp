#ifndef MODIFIABLE_HPP
#define MODIFIABLE_HPP

#include "cards/BaseCard.hpp"

namespace Cards{
class Modifiable : public virtual BaseCard{
public:
    /*
     * updates cards values based on children
     * */
    void refresh(GameServer& game) override;

    /*
     * applies children's changes
     * (ref. implementation, can be changed by inherited classes)
     * */
    virtual void applyChildren(GameServer& game);

    inline virtual ~Modifiable(){}
};
}

#endif

