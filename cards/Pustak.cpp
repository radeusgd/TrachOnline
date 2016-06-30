#include "cards/Pustak.hpp"

using namespace Cards;

string Pustak::getName(){
    return "pustak";
}

CardPtr Pustak::makeNew(){
    return make_shared<Pustak>();
}

void Pustak::played(GameServer& game){
    //does nothing
}
