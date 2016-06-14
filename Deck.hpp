#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <string>
#include "cards/BaseCard.hpp"

using namespace std;

CardPtr makeCardFromName(string);
vector<CardPtr> makeDeck();

#endif /* DECK_HPP */
