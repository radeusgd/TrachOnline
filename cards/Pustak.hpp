#ifndef PUSTAK_HPP
#define PUSTAK_HPP

#include "cards/Playable.hpp"
namespace Cards{
class Pustak : public Playable{ //virtual inheritance needs the base class to be inherited normally exactly once so we inherit it non-virtually at the very last step
public:
    string getName() override;
    CardPtr makeNew() override;
    vector<CardPtr>& getAppliedCards() override;

    int& getCUID() override;
    
    bool& getActiveState() override;

    void played(GameServer& game) override;

    inline virtual ~Pustak(){}
protected:
    vector<CardPtr> appliedCards;
    int cuid;
    bool active=true;
};
}

#endif /* PUSTAK_HPP */
