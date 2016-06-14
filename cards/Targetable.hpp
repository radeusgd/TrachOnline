#ifndef TARGETABLE_HPP
#define TARGETABLE_HPP 

#include "cards/BaseCard.hpp"

namespace Cards{
class Targetable : public virtual BaseCard{
public: 
    int from,to;
    int priority;
    nlohmann::json jsonify() override;
    inline virtual ~Targetable(){}
};
}

#endif /* TARGETABLE_HPP */
