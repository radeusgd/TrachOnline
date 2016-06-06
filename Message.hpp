#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "json.hpp"

using namespace nlohmann;
using namespace std;

struct Message{
	Message();
	Message(string name, json data);
	Message(string text);
	string name;
	json data;
	string toText() const;
};

#endif
