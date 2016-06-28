#include "cards/WielkaLapa.hpp"

using namespace Cards;

string WielkaLapa::getName(){
    return "wielka_lapa";
}

CardPtr WielkaLapa::makeNew(){
    return make_shared<WielkaLapa>();
}

vector<CardPtr>& WielkaLapa::getAppliedCards(){
    return appliedCards;
}

int& WielkaLapa::getOwnerId(){
    return ownerid;
}

int& WielkaLapa::getCUID(){
    return cuid;
}

bool& WielkaLapa::getActiveState(){
    return active;
}

void WielkaLapa::reset(){
    Feature::reset();
    value = 1;
}

void WielkaLapa::apply(GameServer::Player& player){
    player.handCards += value;
}
