#include <PubBus/PubBus.hpp>
#include <iostream>

struct DummyMessage : public pub::Message
{
	int important_value = 0;
};

int main()
{
	pub::MessageBus bus;
	DummyMessage msg;
	msg.important_value = 100;

	bus.subscribe<DummyMessage>(
		[](DummyMessage msg)
		{
			std::cout << "Important value: " << msg.important_value << std::endl;
		}
	);

	bus.publish(msg);
}
