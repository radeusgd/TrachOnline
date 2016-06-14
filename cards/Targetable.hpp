#ifndef TARGETABLE_HPP
#define TARGETABLE_HPP 

#include "cards/Prioritized.hpp"

namespace Cards{
class Targetable : public virtual Prioritized{
public: 
    int from,to;
    int& getPriority() override;
    nlohmann::json jsonify() override;
    inline virtual ~Targetable(){}
protected:
    int priority;
};
}

#endif /* TARGETABLE_HPP */
