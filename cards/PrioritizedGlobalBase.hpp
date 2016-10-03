#ifndef PRIORITIZEDGLOBALBASE_HPP
#define PRIORITIZEDGLOBALBASE_HPP 

#include "cards/GlobalBase.hpp"
#include "cards/Prioritized.hpp"
namespace Cards{
    template<typename T, bool skipOwner, int defaultPriority>
        class PrioritizedGlobalBase : public GlobalBase<T,skipOwner>, public Prioritized
    {
        public:
            int& getPriority() override{
                return priority;
            }
        private:
            int priority = defaultPriority;
    };
}
#endif /* PRIORITIZEDGLOBALBASE_HPP */
