#include "cards/Modifiable.hpp"
#include "cards/Modification.hpp"
using namespace Cards;

void Modifiable::refresh(GameServer& game){
    reset();
    applyChildren(game);
}

void Modifiable::applyChildren(GameServer& game){
    for(auto& card : getAppliedCards()){
        card->refresh(game);
        shared_ptr<Modification> mod = dynamic_pointer_cast<Modification>(card);
        if(mod!=nullptr && mod->getActiveState()){
            mod->apply(this);
        }
    }
}
