#include "cards/Modifiable.hpp"
#include "cards/Modification.hpp"
using namespace Cards;

void Modifiable::refresh(){
    this->prepare();
    this->applyChildren();
}

void Modifiable::applyChildren(){
    for(auto& card : getAppliedCards()){
        shared_ptr<Modification> mod = dynamic_pointer_cast<Modification>(card);
        if(mod!=nullptr && mod->getActiveState()){
            mod->apply(this);
        }
    }
}
