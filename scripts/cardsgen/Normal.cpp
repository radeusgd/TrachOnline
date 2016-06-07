#include "cards/#Name#.hpp"

using namespace Cards;

string #Name#::getName(){
    return "#name#";
}

bool #Name#::canBePlayedAt(CardPtr card){
    if(card==nullptr) return true;
    return false;
}

CardPtr #Name#::makeNew(){
    return make_shared<#Name#>();
}

vector<CardPtr>& #Name#::getAppliedCards(){
    return appliedCards;
}

int& #Name#::getCUID(){
    return cuid;
}
