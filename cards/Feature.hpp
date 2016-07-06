#ifndef FEATURE_HPP
#define FEATURE_HPP

#include "cards/Equipped.hpp"
#include "cards/PlayerModification.hpp"

namespace Cards{
class Feature : public virtual Equipped, public PlayerModification{
public:
    void reset() override;
    inline virtual ~Feature(){}
};
}

#endif
