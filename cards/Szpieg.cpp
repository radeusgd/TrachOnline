#include "cards/Szpieg.hpp"
#include "GameServer.hpp"

using namespace Cards;

string Szpieg::getName(){
    return "szpieg";
}

CardPtr Szpieg::makeNew(){
    return make_shared<Szpieg>();
}

vector<CardPtr>& Szpieg::getAppliedCards(){
    return appliedCards;
}

int& Szpieg::getOwnerId(){
    return ownerid;
}

int& Szpieg::getCUID(){
    return cuid;
}

bool& Szpieg::getActiveState(){
    return active;
}


void Szpieg::played(GameServer& game){
    Message m;
    m.name = "showCards";
    m.data = json::array();
    json j;
    j["pid"] = to;
    j["cards"] = json::array();
    for(auto& c : game.players[to].hand){
        j["cards"].push_back(c->getName());
    }
    m.data.push_back(j);
    game.send(game.players[from].ws,m);
}