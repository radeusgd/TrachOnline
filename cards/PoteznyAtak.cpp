#include "cards/PoteznyAtak.hpp"
#include "GameServer.hpp"

using namespace Cards;

string PoteznyAtak::getName(){
    return "potezny_atak";
}



CardPtr PoteznyAtak::makeNew(){
    return make_shared<PoteznyAtak>();
}

void PoteznyAtak::reset(){
  Atak::reset();
  Atak::value=2;
}
