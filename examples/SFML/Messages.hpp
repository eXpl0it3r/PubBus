#pragma once

#include <PubBus/Message.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

struct WindowMessage : public pub::Message
{
	enum Type {Closed, LostFocus, GainedFocus};
	
	WindowMessage(Type type) : type(type)
	{}

	Type type;
};

struct SizeMessage : public pub::Message
{
	SizeMessage(sf::Vector2u size) : size(size)
	{}

	sf::Vector2u size;
};

struct KeyMessage : public pub::Message
{
	enum Type {Pressed, Release};

	KeyMessage(Type type, sf::Keyboard::Key, bool alt, bool control, bool shift, bool system)
	: type(type), code(code), alt(alt), control(control), system(system)
	{}

	Type type;
	sf::Keyboard::Key code;
	bool alt;
	bool control;
	bool shift;
	bool system;
};

struct TextMessage : public pub::Message
{
	TextMessage(sf::Uint32 unicode) : unicode(unicode)
	{}

	sf::Uint32 unicode;
};

struct MouseMoveMessage : public pub::Message
{
	MouseMoveMessage(sf::Vector2i position) : position(position)
	{}

	sf::Vector2i position;
};

struct MouseButtonMessage : public pub::Message
{
	enum Type {Pressed, Release};

	MouseButtonMessage(Type type, sf::Mouse::Button button, sf::Vector2i position)
	: type(type), button(button), position(position)
	{}

	Type type;
	sf::Mouse::Button button;
	sf::Vector2i position;
};

struct MouseWheelScrollMessage : public pub::Message
{
	MouseWheelScrollMessage(sf::Mouse::Wheel wheel, float delta, sf::Vector2i position)
	: wheel(wheel), delta(delta), position(position)
	{}

	sf::Mouse::Wheel wheel;
	float delta;
	sf::Vector2i position;
};
