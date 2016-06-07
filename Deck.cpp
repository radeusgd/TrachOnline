#include "Deck.hpp"

#include "cards/Pustak.hpp"
#include "cards/Atak.hpp"

using namespace Cards;

inline void addCards(vector<CardPtr>& deck, CardPtr type, int amount){
    for(int i=0;i<amount;++i)
        deck.push_back(type->makeNew());
}

vector<CardPtr> makeDeck(){
    vector<CardPtr> deck;
    addCards(deck, make_shared<Pustak>(), 20);
    addCards(deck, make_shared<Atak>(), 40);
    //TODO other cards
    
    return deck;
}
