#include "cards/WielkaLapa.hpp"

using namespace Cards;

string WielkaLapa::getName(){
    return "wielka_lapa";
}

CardPtr WielkaLapa::makeNew(){
    return make_shared<WielkaLapa>();
}

void WielkaLapa::reset(){
    Feature::reset();
    value = 1;
}

void WielkaLapa::apply(GameServer::Player& player){
    player.handCards += value;
}
