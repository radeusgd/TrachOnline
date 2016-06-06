#ifndef PUSTAK_HPP
#define PUSTAK_HPP

#include "cards/BaseCard.hpp"

class Pustak : public BaseCard{
    public:
        string getName() override;
        bool canBePlayedAt(BaseCard* card) override;

        inline virtual ~Pustak(){}
};

#endif /* PUSTAK_HPP */
