#include "cards/BaseCard.hpp"

using namespace Cards;
using namespace nlohmann;

json BaseCard::jsonify(){
    json o;
    o["name"] = this->getName();
    for(auto& card : this->getAppliedCards()){
        o["attached"].push_back(card->jsonify());
    }
}
