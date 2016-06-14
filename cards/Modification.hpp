#ifndef MODIFICATION_HPP
#define MODIFICATION_HPP

#include "cards/BaseCard.hpp"

namespace Cards{
class Modification : public virtual BaseCard{
public:
    virtual void apply(BaseCard* parent)=0;
    inline virtual ~Modification(){}
};
}

#endif

