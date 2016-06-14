#ifndef MODIFIABLE_HPP
#define MODIFIABLE_HPP

#include "cards/BaseCard.hpp"

namespace Cards{
class Modifiable : public virtual BaseCard{
public:
    virtual void applyChildren();
    inline virtual ~Modifiable(){}
};
}

#endif

