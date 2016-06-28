#ifndef ENHANCEABLE_HPP
#define ENHANCEABLE_HPP 
#include "cards/BaseCard.hpp"
namespace Cards{
class Enhanceable : public virtual BaseCard{
public: 
    /* card's value that can be enhanced, eg. amounf of damage of an attack */
    int value;

    //TODO maybe a standard method for processing?

    inline virtual ~Enhanceable(){}
};
}

#endif /* ENHANCEABLE_HPP */
