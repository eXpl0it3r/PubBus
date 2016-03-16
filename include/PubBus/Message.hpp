#pragma once

#include <typeinfo>
#include <typeindex>

class Message
{
public:
	using Id = std::type_index;

public:
	template<typename T>
	static Id id();
};

template<typename T>
Message::Id Message::id()
{
	return std::type_index(typeid(T));
}
