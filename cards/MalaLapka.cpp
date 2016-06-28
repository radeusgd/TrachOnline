#include "cards/MalaLapka.hpp"

using namespace Cards;

string MalaLapka::getName(){
    return "mala_lapka";
}

CardPtr MalaLapka::makeNew(){
    return make_shared<MalaLapka>();
}

vector<CardPtr>& MalaLapka::getAppliedCards(){
    return appliedCards;
}

int& MalaLapka::getOwnerId(){
    return ownerid;
}

int& MalaLapka::getCUID(){
    return cuid;
}

bool& MalaLapka::getActiveState(){
    return active;
}

void MalaLapka::reset(){
    Feature::reset();
    value = 1;
}

void MalaLapka::apply(GameServer::Player& player){
    player.handCards -= value;
}
