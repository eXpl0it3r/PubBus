#include <PubBus/PubBus.hpp>
#include <iostream>

struct DummyMessage : public pub::Message
{
	int important_value = 0;
};

int main()
{
    auto bus = pub::MessageBus{};
    auto msg = DummyMessage{};
	msg.important_value = 100;

	bus.subscribe<DummyMessage>(
		[](DummyMessage msg)
		{
			std::cout << "Important value: " << msg.important_value << "\n";
		}
	);

	bus.publish(msg);
}
