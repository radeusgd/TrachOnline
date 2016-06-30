#include "cards/Rzut.hpp"
#include "GameServer.hpp"

using namespace Cards;

string Rzut::getName(){
    return "rzut";
}

bool Rzut::canBePlayedAt(CardPtr card, GameServer* game){
    if(card==nullptr) return true;
    return false;
}

CardPtr Rzut::makeNew(){
    return make_shared<Rzut>();
}

void Rzut::played(GameServer& game){
    if(getAppliedCards().size()>=1){
        game.players[to].hand.push_back(getAppliedCards()[0]);//give the target attached cards (should be only one)
        game.updateCards(game.players[to]);
    }
}
