#ifndef PLAYERMODIFICATION_HPP
#define PLAYERMODIFICATION_HPP

#include "cards/BaseCard.hpp"
#include "GameServer.hpp"

namespace Cards{
class PlayerModification : public virtual BaseCard{
public:
    virtual void apply(GameServer::Player& player)=0;
    inline virtual ~PlayerModification(){}
};
}

#endif

