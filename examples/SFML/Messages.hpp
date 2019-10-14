#pragma once

#include <PubBus/Message.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

struct WindowMessage : public pub::Message
{
    enum Type
    {
        Closed,
        LostFocus,
        GainedFocus
    };

    WindowMessage(const Type type)
        : type{ type }
    {}

    Type type;
};

struct SizeMessage : public pub::Message
{
    SizeMessage(const sf::Vector2u size)
        : size{ size }
    {}

    sf::Vector2u size;
};

struct KeyMessage : public pub::Message
{
    enum Type
    {
        Pressed,
        Released
    };

    KeyMessage(const Type type, const sf::Keyboard::Key code, const bool alt, const bool control, const bool shift, const bool system)
        : type{ type }
        , code{ code }
        , alt{ alt }
        , control{ control }
        , shift{ shift }
        , system{ system }
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
    TextMessage(const sf::Uint32 unicode)
        : unicode{ unicode }
    {}

    sf::Uint32 unicode;
};

struct MouseMoveMessage : public pub::Message
{
    MouseMoveMessage(const sf::Vector2i position)
        : position{ position }
    {}

    sf::Vector2i position;
};

struct MouseButtonMessage : public pub::Message
{
    enum Type
    {
        Pressed,
        Released
    };

    MouseButtonMessage(const Type type, const sf::Mouse::Button button, const sf::Vector2i position)
        : type{ type }
        , button{ button }
        , position{ position }
    {}

    Type type;
    sf::Mouse::Button button;
    sf::Vector2i position;
};

struct MouseWheelScrollMessage : public pub::Message
{
    MouseWheelScrollMessage(const sf::Mouse::Wheel wheel, const float delta, const sf::Vector2i position)
        : wheel{ wheel }
        , delta{ delta }
        , position{ position }
    {}

    sf::Mouse::Wheel wheel;
    float delta;
    sf::Vector2i position;
};
