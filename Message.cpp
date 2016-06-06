#include "Message.hpp"

Message::Message(){}
Message::Message(string name, json data) : name(name), data(data) {}
Message::Message(string text){
	json msg = json::parse(text);
	name = msg["name"];
	data = msg["data"];
}
string Message::toText() const{
	json msg;
	msg["name"] = name;
	msg["data"] = data;
	return msg.dump();
}
