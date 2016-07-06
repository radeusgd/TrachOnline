#ifndef TURNBASED_HPP
#define TURNBASED_HPP

#include "cards/Equipped.hpp"
#include "GameServer.hpp"
namespace Cards{
  class TurnBased;
}

namespace Cards{
class TurnBased : public virtual Equipped{
public:
    inline virtual void execute(GameServer& game, GameServer::Player& p){};
    inline virtual ~TurnBased(){}
};
}

#endif
