#ifndef PUSTAK_HPP
#define PUSTAK_HPP

#include "cards/Playable.hpp"

class Pustak : public Playable{ 
public:
    string getName() override;
    bool canBePlayedAt(shared_ptr<BaseCard> card) override;
    shared_ptr<BaseCard> makeNew() override;

    void played() override;

    inline virtual ~Pustak(){}
};

#endif /* PUSTAK_HPP */
