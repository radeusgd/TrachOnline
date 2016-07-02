#include "cards/MalaLapka.hpp"

using namespace Cards;

string MalaLapka::getName(){
    return "mala_lapka";
}

CardPtr MalaLapka::makeNew(){
    return make_shared<MalaLapka>();
}

void MalaLapka::reset(){
    Feature::reset();
    value = 1;
}

void MalaLapka::apply(GameServer::Player& player){
    player.handCards -= value;
}
