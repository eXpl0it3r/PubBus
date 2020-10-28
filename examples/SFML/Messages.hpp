#pragma once

#include <PubBus/Message.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

struct WindowMessage : pub::Message
{
    enum class Type
    {
        Closed,
        LostFocus,
        GainedFocus
    };

    Type type;
};

struct SizeMessage : pub::Message
{
    sf::Vector2u size;
};

struct KeyMessage : pub::Message
{
    enum class Type
    {
        Pressed,
        Released
    };

    Type type;
    sf::Keyboard::Key code;
    bool alt;
    bool control;
    bool shift;
    bool system;
};

struct TextMessage : pub::Message
{
    sf::Uint32 unicode;
};

struct MouseMoveMessage : pub::Message
{
    sf::Vector2i position;
};

struct MouseButtonMessage : pub::Message
{
    enum class Type
    {
        Pressed,
        Released
    };

    Type type;
    sf::Mouse::Button button;
    sf::Vector2i position;
};

struct MouseWheelScrollMessage : pub::Message
{
    sf::Mouse::Wheel wheel;
    float delta;
    sf::Vector2i position;
};
