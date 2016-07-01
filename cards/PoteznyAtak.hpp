#ifndef POTEZNY_ATAK_HPP
#define POTEZNY_ATAK_HPP

#include "cards/Atak.hpp"

namespace Cards{
class PoteznyAtak : public Atak{
public:
    string getName() override;

    CardPtr makeNew() override;

    void reset() override;

    inline virtual ~PoteznyAtak(){}

};
}

#endif
