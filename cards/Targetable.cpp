#include "cards/Targetable.hpp"

using namespace Cards;
using namespace nlohmann;

void Targetable::reset(){
    BaseCard::reset();
    priority = 0;//default priority is 0 (for things like Zamiana etc.)
    to = initialTo;
    from = initialFrom;
}

int& Targetable::getPriority(){
    return priority;
}

json Targetable::jsonify(){
    json o;
    o["name"] = this->getName();
    o["from"] = initialFrom;
    o["to"] = initialTo.playerId;//FIXME serialize a tuple not just the int!
    o["attached"] = json::array();
    o["id"] = this->getCUID();
    for(auto& card : this->getAppliedCards()){
        o["attached"].push_back(card->jsonify());
    }
    return o;
}
