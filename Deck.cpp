#include "Deck.hpp"

#include <tuple>

#include "cards/Pustak.hpp"
#include "cards/Atak.hpp"
#include "cards/ZmasowanyAtak.hpp"
#include "cards/Obrona.hpp"
#include "cards/Odbicie.hpp"
#include "cards/Przerzut.hpp"
#include "cards/Wzmocnienie.hpp"
#include "cards/Uzdrowienie.hpp"

using namespace Cards;

CardPtr makeCardFromName(string name){
    static map<string,CardPtr> types;
    if(types.empty()){
        //initialize types
        types["pustak"] = make_shared<Pustak>();
        types["atak"] = make_shared<Atak>();
        types["zmasowany_atak"] = make_shared<ZmasowanyAtak>();
        types["obrona"] = make_shared<Obrona>();
        types["odbicie"] = make_shared<Odbicie>();
        types["przerzut"] = make_shared<Przerzut>();
        types["wzmocnienie"] = make_shared<Wzmocnienie>();
        types["uzdrowienie"] = make_shared<Uzdrowienie>();
    }
    if(types[name]) return types[name]->makeNew();
    return nullptr;
}

tuple<string,int> basedeck[] = {
    make_tuple("pustak",5),
    make_tuple("atak",12+2),
    make_tuple("zmasowany_atak",5),
    make_tuple("obrona",5),
    make_tuple("odbicie",5),
    make_tuple("przerzut",5),
    make_tuple("wzmocnienie",3),
    make_tuple("uzdrowienie",5+1+2),
};
vector<CardPtr> makeDeck(){
    vector<CardPtr> deck;
    for(auto t : basedeck){
        for(int i=0;i<get<1>(t);++i){
            deck.push_back(makeCardFromName(get<0>(t)));
        }
    }
    return deck;
}
