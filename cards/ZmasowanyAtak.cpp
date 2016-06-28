#include "cards/ZmasowanyAtak.hpp"
#include "cards/Atak.hpp"
#include "GameServer.hpp"

using namespace Cards;

string ZmasowanyAtak::getName(){
    return "zmasowany_atak";
}

bool ZmasowanyAtak::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr ZmasowanyAtak::makeNew(){
    return make_shared<ZmasowanyAtak>();
}

vector<CardPtr>& ZmasowanyAtak::getAppliedCards(){
    return appliedCards;
}

int& ZmasowanyAtak::getOwnerId(){
    return ownerid;
}
int& ZmasowanyAtak::getCUID(){
    return cuid;
}

bool& ZmasowanyAtak::getActiveState(){
    return active;
}

void ZmasowanyAtak::refresh(GameServer& game){
    reset();
    if(!childrenPrepared){
        prepareChildren(game);
    }
    BaseCard::refresh(game);//here we apply all classic Modifications
    for(auto& card : getAppliedCards()){
        shared_ptr<Atak> atk = dynamic_pointer_cast<Atak>(card);
        if(atk!=nullptr){
            atk->reset();//reset to original
            atk->value = this->value;//update from global value
            atk->getPriority() = this->priority;//update from global value
            //atk->refresh(game);//can't use this as we need to inject value between prepare and applyChildren
            atk->applyChildren(game);//apply additional modifiers
        }
    }
}

void ZmasowanyAtak::reset(){
    BaseCard::reset();
    priority = 6;
    value=1;
    active=true;
}

int& ZmasowanyAtak::getPriority(){
    return priority;
}

void ZmasowanyAtak::played(GameServer& game){
    for(auto& card : getAppliedCards()){
        //we don't refresh attacks here as they have been refreshed with the base
        shared_ptr<Atak> atk = dynamic_pointer_cast<Atak>(card);
        if(atk!=nullptr && atk->getActiveState()){
            atk->played(game);
        }
    }
}

void ZmasowanyAtak::prepareChildren(GameServer& game){
    for(int i=0;i<game.players.size();++i){
        if(i!=getOwnerId()){//don't attack the owner
            auto atak = make_shared<Atak>();
            atak->initialFrom=getOwnerId();
            atak->initialTo=i;
            game.addCardToTable(atak);
            this->getAppliedCards().push_back(atak);
        }
    }
    childrenPrepared = true;
}

json ZmasowanyAtak::jsonify(){
    json o;
    o["name"] = this->getName();
    o["from"] = getOwnerId();
    o["attached"] = json::array();
    o["id"] = this->getCUID();
    for(auto& card : this->getAppliedCards()){
        o["attached"].push_back(card->jsonify());
    }
    return o;
}
