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
#include "cards/PotezneUzdrowienie.hpp"
#include "cards/PelnaRegeneracja.hpp"
#include "cards/Nowonarodzony.hpp"
#include "cards/WymianaKart.hpp"
#include "cards/Zamiana.hpp"
#include "cards/Rzut.hpp"
#include "cards/Szpieg.hpp"
#include "cards/Trening.hpp"
#include "cards/Oslabienie.hpp"
#include "cards/Superwytrzymaly.hpp"
#include "cards/Nadwrazliwy.hpp"
#include "cards/Gruboskorny.hpp"
#include "cards/Berserk.hpp"
#include "cards/Kot.hpp"
#include "cards/WielkaLapa.hpp"
#include "cards/MalaLapka.hpp"

using namespace Cards;

CardPtr makeCardFromName(string name){
    static map<string,CardPtr> types;
    if(types.empty()){
        //initialize types
        CardPtr typeList[] = {
            make_shared<Pustak>(),
            make_shared<Atak>(),
            make_shared<ZmasowanyAtak>(),
            make_shared<Obrona>(),
            make_shared<Odbicie>(),
            make_shared<Przerzut>(),
            make_shared<Wzmocnienie>(),
            make_shared<Uzdrowienie>(),
            make_shared<PotezneUzdrowienie>(),
            make_shared<PelnaRegeneracja>(),
            make_shared<Nowonarodzony>(),
            make_shared<WymianaKart>(),
            make_shared<Zamiana>(),
            make_shared<Rzut>(),
            make_shared<Szpieg>(),
            make_shared<Trening>(),
            make_shared<Oslabienie>(),
            make_shared<Superwytrzymaly>(),
            make_shared<Nadwrazliwy>(),
            make_shared<Gruboskorny>(),
            make_shared<Berserk>(),
            make_shared<Kot>(),
            make_shared<WielkaLapa>(),
            make_shared<MalaLapka>(),
        };
        for(auto type : typeList){
            types[type->getName()] = type;
        }
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
    make_tuple("uzdrowienie",5),
    make_tuple("potezne_uzdrowienie",2),
    make_tuple("pelna_regeneracja",1),
    make_tuple("nowonarodzony",1),
    make_tuple("wymiana_kart",1),
    make_tuple("zamiana",1),
    //make_tuple("rzut",2),
    make_tuple("szpieg",2),
    make_tuple("trening",2),
    make_tuple("oslabienie",1),
    make_tuple("superwytrzymaly",1),
    make_tuple("nadwrazliwy",1),
    make_tuple("gruboskorny",1),
    make_tuple("berserk",1),
    make_tuple("kot",1),
    make_tuple("wielka_lapa",1),
    make_tuple("mala_lapka",1),
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
