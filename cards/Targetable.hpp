#ifndef TARGETABLE_HPP
#define TARGETABLE_HPP

#include "cards/Prioritized.hpp"
#include "Target.hpp"

namespace Cards{
class Targetable : public virtual Prioritized{
public:
    int from,initialFrom;
    Target to,initialTo;
    void reset() override;
    int& getPriority() override;
    virtual bool canBeTargetedAt(Target t)=0;
    nlohmann::json jsonify() override;
    inline virtual ~Targetable(){}
protected:
    int priority;
};
}

#endif /* TARGETABLE_HPP */
