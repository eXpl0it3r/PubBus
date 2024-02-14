#include <PubBus/PubBus.hpp>
#include <iostream>

struct DummyMessage : pub::Message
{
    int important_value = 0;
};

int main()
{
    auto bus = pub::MessageBus{};
    const auto message = DummyMessage{ .important_value = 100 };

    bus.subscribe<DummyMessage>(
        [](const DummyMessage& message)
        {
            std::cout << "Important value: " << message.important_value << "\n";
        }
    );

    bus.publish(message);
}
