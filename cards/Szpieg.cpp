#include "cards/Szpieg.hpp"
#include "GameServer.hpp"

using namespace Cards;

string Szpieg::getName(){
    return "szpieg";
}

CardPtr Szpieg::makeNew(){
    return make_shared<Szpieg>();
}

void Szpieg::reset(){
    Targetable::reset();
    priority = 6;
    active=true;
}

void Szpieg::played(GameServer& game){
    Message m;
    m.name = "showCards";
    m.data = json::array();
    json j;
    j["pid"] = to.playerId;
    j["cards"] = json::array();
    for(auto& c : game.players[to.playerId].hand){
        j["cards"].push_back(c->getName());
    }
    m.data.push_back(j);
    game.send(game.players[from].ws,m);
}
