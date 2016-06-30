#include "cards/#Name#.hpp"

using namespace Cards;

string #Name#::getName(){
    return "#name#";
}

bool #Name#::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr #Name#::makeNew(){
    return make_shared<#Name#>();
}

