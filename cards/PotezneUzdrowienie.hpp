#ifndef POTEZNEUZDROWIENIE_HPP
#define POTEZNEUZDROWIENIE_HPP

#include "cards/Uzdrowienie.hpp"

namespace Cards{
class PotezneUzdrowienie : public Uzdrowienie{
public:
    string getName() override;
    
    CardPtr makeNew() override;

    void reset() override;

    inline virtual ~PotezneUzdrowienie(){};
};
}

#endif
