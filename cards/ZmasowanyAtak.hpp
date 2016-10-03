#ifndef ZMASOWANYATAK_HPP
#define ZMASOWANYATAK_HPP

#include "cards/PrioritizedGlobalBase.hpp"
#include "cards/Atak.hpp"
#include "cards/Enhanceable.hpp"

namespace Cards{
class ZmasowanyAtak : public PrioritizedGlobalBase<Atak,true,6>, public Enhanceable
{
protected:
    void updateChild(shared_ptr<Atak> child) override;
};
}

#endif

