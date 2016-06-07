#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <memory>
#include "cards/BaseCard.hpp"

using namespace std;

vector<Cards::CardPtr> makeDeck();

#endif /* DECK_HPP */
