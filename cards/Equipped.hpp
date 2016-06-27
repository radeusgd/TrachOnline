#ifndef EQUIPPED_HPP
#define EQUIPPED_HPP

#include "cards/Targetable.hpp"
namespace Cards{
    class Equipped;
}
#include "GameServer.hpp"

namespace Cards{
class Equipped : public virtual Targetable{
public:
    bool canBePlayedAt(CardPtr card, GameServer* game) override;
    inline virtual void equip(GameServer::Player& player, GameServer& game){};
    inline virtual ~Equipped(){}
};
}

#endif

