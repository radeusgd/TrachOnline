#include "cards/KradziezKarty.hpp"
#include <random>
#include "GameServer.hpp"

using namespace Cards;

string KradziezKarty::getName(){
    return "kradziez_karty";
}

CardPtr KradziezKarty::makeNew(){
    return make_shared<KradziezKarty>();
}

vector<CardPtr>& KradziezKarty::getAppliedCards(){
    return appliedCards;
}

int& KradziezKarty::getOwnerId(){
    return ownerid;
}

int& KradziezKarty::getCUID(){
    return cuid;
}

bool& KradziezKarty::getActiveState(){
    return active;
}

void KradziezKarty::reset(){
    Targetable::reset();
    priority = 6;
}

void KradziezKarty::played(GameServer& game){
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> uni(0,game.players[to].hand.size());
    int chosen = uni(g);
    CardPtr card = game.players[to].hand[chosen];
    game.players[to].hand.erase(game.players[to].hand.begin()+chosen);
    game.players[from].hand.push_back(card);
    game.fillCards(game.players[to]);
    game.fillCards(game.players[from]);
}
