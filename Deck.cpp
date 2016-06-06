#include "Deck.hpp"

#include "cards/Pustak.hpp"

inline void addCards(vector<shared_ptr<BaseCard>>& deck, shared_ptr<BaseCard> type, int amount){
    for(int i=0;i<amount;++i)
        deck.push_back(type->makeNew());
}

vector<shared_ptr<BaseCard>> makeDeck(){
    vector<shared_ptr<BaseCard>> deck;
    addCards(deck, make_shared<Pustak>(), 40);
    //TODO other cards
    
    return deck;
}
