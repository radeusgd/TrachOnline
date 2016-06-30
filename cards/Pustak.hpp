#ifndef PUSTAK_HPP
#define PUSTAK_HPP

#include "cards/Playable.hpp"
#include "cards/BaseCardImpl.hpp"
namespace Cards{
class Pustak : public Playable, public BaseCardImpl{ //virtual inheritance needs the base class to be inherited normally exactly once so we inherit it non-virtually at the very last step
public:
    string getName() override;
    CardPtr makeNew() override;
    void played(GameServer& game) override;

    inline virtual ~Pustak(){}
};
}

#endif /* PUSTAK_HPP */
