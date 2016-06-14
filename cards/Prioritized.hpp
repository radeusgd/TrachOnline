#ifndef PRIORITIZED_HPP
#define PRIORITIZED_HPP

#include "cards/BaseCard.hpp"

namespace Cards{
class Prioritized : public virtual BaseCard{
public:
    virtual int& getPriority()=0;
    inline virtual ~Prioritized(){}
};
}

#endif

