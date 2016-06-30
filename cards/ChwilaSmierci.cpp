#include "cards/ChwilaSmierci.hpp"
#include "GameServer.hpp"

using namespace Cards;

string ChwilaSmierci::getName(){
    return "chwila_smierci";
}

bool ChwilaSmierci::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr ChwilaSmierci::makeNew(){
    return make_shared<ChwilaSmierci>();
}

void ChwilaSmierci::played(GameServer& game){
    for(GameServer::Player& p : game.players){
        if(p.HP>0) p.HP=1;
    }
}
