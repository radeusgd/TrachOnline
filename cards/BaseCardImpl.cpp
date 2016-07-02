#include "cards/BaseCardImpl.hpp"

using namespace Cards;

vector<CardPtr>& BaseCardImpl::getAppliedCards(){
    return appliedCards;
}

int& BaseCardImpl::getOwnerId(){
    return ownerid;
}

int& BaseCardImpl::getCUID(){
    return cuid;
}

bool& BaseCardImpl::getActiveState(){
    return active;
}

