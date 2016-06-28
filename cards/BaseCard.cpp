#include "cards/BaseCard.hpp"
#include "cards/Modification.hpp"

using namespace Cards;
using namespace nlohmann;

void BaseCard::refresh(GameServer& game){
    reset();
    applyChildren(game);
}

void BaseCard::applyChildren(GameServer& game){
    for(auto& card : getAppliedCards()){
        card->refresh(game);
        shared_ptr<Modification> mod = dynamic_pointer_cast<Modification>(card);
        if(mod!=nullptr && mod->getActiveState()){
            mod->apply(this);
            //cout<<"applied "<<mod->getName()<<" to "<<getName()<<endl;
        }
    }
}

json BaseCard::jsonify(){
    json o;
    o["name"] = this->getName();
    o["attached"] = json::array();
    o["id"] = this->getCUID();
    for(auto& card : this->getAppliedCards()){
        o["attached"].push_back(card->jsonify());
    }
    return o;
}
