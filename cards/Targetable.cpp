#include "cards/Targetable.hpp"

using namespace Cards;
using namespace nlohmann;

json Targetable::jsonify(){
    json o;
    o["name"] = this->getName();
    o["from"] = from;
    o["to"] = to;
    o["attached"] = json::array();
    o["id"] = this->getCUID();
    for(auto& card : this->getAppliedCards()){
        o["attached"].push_back(card->jsonify());
    }
    return o;
}
