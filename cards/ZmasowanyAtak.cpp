#include "cards/ZmasowanyAtak.hpp"
#include "GameServer.hpp"

using namespace Cards;

void ZmasowanyAtak::updateChild(shared_ptr<Atak> child){
    child->value = value;
}
