#ifndef GLOBALBASE_HPP
#define GLOBALBASE_HPP

#include <type_traits>
#include "cards/Playable.hpp"
#include "cards/Targetable.hpp"
#include "cards/BaseCardImpl.hpp"
#include "GameServer.hpp"
using namespace std;//TODO might want to not include namesaces in headers?
namespace Cards{
    template<typename T,bool skipOwner>
    class GlobalBase : public Playable, public BaseCardImpl//TODO should inherit BCI or not
    {
        static_assert(std::is_base_of<Playable,T>::value && std::is_base_of<Targetable,T>::value,"T has to be both Playable and Targetable");
        public:
        string getName() override{
            //TODO super inefficient, but we need to respond to this query in various states (when card is not prepared or refreshed) so there doesn't seem to be a better way
            //may want to add if(childrenPrepared) return getAppliedCards()[0]->getName()+"_global"; or something like this
            T t;//despita normal practice we use stack for speed; if this turns out to be a problem we may move to dynamic allocation
            return t.getName()+"_global";
        }
        CardPtr makeNew() override{
            return make_shared<GlobalBase<T,skipOwner>>();
        }
        void refresh(GameServer& game) override{
            if(!childrenPrepared){
                prepareChildren(game);
            }
            BaseCard::refresh(game);//here we apply all classic Modifications
            for(auto& card : getAppliedCards()){
                shared_ptr<T> c = dynamic_pointer_cast<T>(card);
                if(c!=nullptr){
                    c->reset();//reset to original
                    updateChild(c);
                    c->applyChildren(game);//apply additional modifiers
                }
            }
        }
        void played(GameServer& game) override{
            for(auto& card : getAppliedCards()){
                shared_ptr<T> c = dynamic_pointer_cast<T>(card);
                if(c!=nullptr && c->getActiveState()){
                    c->played(game);
                }
            }
        }
        protected:
        virtual void updateChild(shared_ptr<T> child){}
        private:
        bool childrenPrepared = false;
        void prepareChildren(GameServer& game){
            for(int i=0;i<game.players.size();++i){
                if(i==getOwnerId() && skipOwner) continue;
                
                auto c = make_shared<T>();
                c->initialFrom=getOwnerId();
                c->initialTo=Target(i,-1);
                game.addCardToTable(c);
                this->getAppliedCards().push_back(c);
            }
            childrenPrepared = true;
        }
    };
};

#endif /* GLOBALBASE_HPP */
