#include <SFML/Graphics.hpp>
#include <PubBus/PubBus.hpp>
#include <string>

#include "Messages.hpp"

using namespace std::string_literals;

class PositionText final : public sf::Drawable
{
public:
    explicit PositionText(const sf::Font& font)
        : m_text{ "0, 0", font }
    {
        
    }

    void setPosition(const sf::Vector2f position)
    {
        m_text.setPosition(position);
    }

    void onMouseMove(const MouseMoveMessage& message)
    {
        m_text.setString(std::to_string(message.position.x) + ", " + std::to_string(message.position.y));
    }

    void onMouseScroll(const MouseWheelScrollMessage& message)
    {
        m_text.setString(std::to_string(message.wheel) + ": " + std::to_string(message.delta));
    }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override final
    {
        target.draw(m_text, states);
    }

    sf::Text m_text;
};

class ButtonText final : public sf::Drawable
{
public:
    explicit ButtonText(const sf::Font& font)
        : m_text{ "Pressed / Released", font }
    {

    }

    void setPosition(const sf::Vector2f position)
    {
        m_text.setPosition(position);
    }

    void onKeyEvent(const KeyMessage& message)
    {
        const auto type = message.type == KeyMessage::Pressed ? "Pressed"s : "Released"s;
        m_text.setString(type + ": " + std::to_string(message.code));
    }

    void onMouseEvent(const MouseButtonMessage& message)
    {
        const auto type = message.type == MouseButtonMessage::Pressed ? "Pressed"s : "Released"s;
        m_text.setString(type + ": " + std::to_string(message.button));
    }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override final
    {
        target.draw(m_text, states);
    }

    sf::Text m_text;
};

int main()
{
    sf::RenderWindow window({ 800, 600 }, "PubBus SFML Test");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("GoudyBookletter1911.otf"))
    {
        return -1;
    }

    PositionText positionText(font);
    positionText.setPosition({ 0.f, 0.f });
    PositionText scrollText(font);
    scrollText.setPosition({ 0.f, 50.f });
    ButtonText keyText(font);
    keyText.setPosition({ 0.f, 100.f });
    ButtonText mouseText(font);
    mouseText.setPosition({ 0.f, 150.f });

    pub::MessageBus bus;

    bus.subscribe<WindowMessage>([&window](const WindowMessage& message)
    {
        if (message.type == WindowMessage::Closed)
        {
            window.close();
        }
    });
    bus.subscribe<MouseMoveMessage>(std::bind(&PositionText::onMouseMove, &positionText, std::placeholders::_1));
    bus.subscribe<MouseWheelScrollMessage>(std::bind(&PositionText::onMouseScroll, &scrollText, std::placeholders::_1));
    bus.subscribe<KeyMessage>([&keyText](const KeyMessage& message) { keyText.onKeyEvent(message); });
    bus.subscribe<MouseButtonMessage>([&mouseText](const MouseButtonMessage& message) { mouseText.onMouseEvent(message); });

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                bus.publish<WindowMessage>({ WindowMessage::Closed });
                break;
            case sf::Event::Resized:
                bus.publish<SizeMessage>({ { event.size.width, event.size.height } });
                break;
            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
                bus.publish<WindowMessage>({ event.type == sf::Event::LostFocus ? WindowMessage::LostFocus : WindowMessage::GainedFocus });
                break;
            case sf::Event::MouseMoved:
                bus.publish<MouseMoveMessage>({ { event.mouseMove.x, event.mouseMove.y } });
                break;
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
                bus.publish<KeyMessage>({
                    event.type == sf::Event::KeyPressed ? KeyMessage::Pressed : KeyMessage::Released,
                    event.key.code,
                    event.key.alt,
                    event.key.control,
                    event.key.shift,
                    event.key.system
                });
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
                bus.publish<MouseButtonMessage>({
                    event.type == sf::Event::MouseButtonPressed ? MouseButtonMessage::Pressed : MouseButtonMessage::Released,
                    event.mouseButton.button,
                    { event.mouseButton.x, event.mouseButton.y }
                });
                break;
            case sf::Event::MouseWheelScrolled:
                bus.publish<MouseWheelScrollMessage>({ event.mouseWheelScroll.wheel, event.mouseWheelScroll.delta, { event.mouseWheelScroll.x, event.mouseWheelScroll.y } });
                break;
            case sf::Event::TextEntered:
                bus.publish<TextMessage>({ event.text.unicode });
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(positionText);
        window.draw(scrollText);
        window.draw(keyText);
        window.draw(mouseText);
        window.display();
    }
}
