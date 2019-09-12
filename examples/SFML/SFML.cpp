#include <SFML/Graphics.hpp>
#include <PubBus/PubBus.hpp>
#include <iostream>
#include "Messages.hpp"

class Position : public sf::Drawable
{
public:
	Position(const sf::Font& font)
	: m_text("0, 0", font)
	{
		
	}

	void OnMouseMove(MouseMoveMessage msg)
	{
		m_text.setString(std::to_string(msg.position.x) + ", " + std::to_string(msg.position.y));
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final
	{
		target.draw(m_text, states);
	}

private:
	sf::Text m_text;
};

int main()
{
	sf::RenderWindow window({ 800, 600 }, "PubBus SFML Test");
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("GoudyBookletter1911.otf");

	Position pos(font);

	pub::MessageBus bus;
	bus.subscribe<WindowMessage>([&window](WindowMessage msg)
	{
		if(msg.type == WindowMessage::Closed)
			window.close();
	});
	bus.subscribe<MouseMoveMessage>([&pos](MouseMoveMessage msg) {pos.OnMouseMove(msg); });
	bus.subscribe<MouseMoveMessage>(std::bind(&Position::OnMouseMove, &pos, std::placeholders::_1));

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				bus.publish<WindowMessage>({ WindowMessage::Closed });
				break;
			case sf::Event::Resized:
				bus.publish<SizeMessage>({ {event.size.width, event.size.height} });
				break;
			case sf::Event::LostFocus:
				bus.publish<WindowMessage>({ WindowMessage::LostFocus });
				break;
			case sf::Event::GainedFocus:
				bus.publish<WindowMessage>({ WindowMessage::GainedFocus });
				break;
			case sf::Event::MouseMoved:
				bus.publish<MouseMoveMessage>({ {event.mouseMove.x, event.mouseMove.y} });
				break;

			}
		}

		window.clear();
		window.draw(pos);
		window.display();
	}
}
