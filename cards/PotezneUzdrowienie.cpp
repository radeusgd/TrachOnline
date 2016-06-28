#include "cards/PotezneUzdrowienie.hpp"
#include "GameServer.hpp"

using namespace Cards;

string PotezneUzdrowienie::getName(){
    return "potezne_uzdrowienie";
}

CardPtr PotezneUzdrowienie::makeNew(){
    return make_shared<PotezneUzdrowienie>();
}

void PotezneUzdrowienie::reset(){
    Uzdrowienie::reset();
    value=2;
}
