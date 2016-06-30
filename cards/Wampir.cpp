#include "cards/Wampir.hpp"

using namespace Cards;

string Wampir::getName(){
    return "wampir";
}

CardPtr Wampir::makeNew(){
    return make_shared<Wampir>();
}

void Wampir::apply(GameServer::Player& player){
    player.wampir=true;
}
