#include "catch.hpp"
#include <PubBus/Message.hpp>
#include <PubBus/MessageBus.hpp>

TEST_CASE("Adding subscriber returns a valid SubscriberHandle", "[MessageBus]")
{
    // Arrange
    struct DummyMessage : pub::Message
    {
    };

    auto bus = pub::MessageBus{};

    // Act
    auto handle = bus.subscribe<DummyMessage>([](DummyMessage msg) {});

    // Assert
    REQUIRE(bus.validate<DummyMessage>(handle) == true);
}

TEST_CASE("Publishing message hands message to subscriber", "[MessageBus]")
{
    // Arrange
    struct DummyMessage : pub::Message
    {
        int data;
    };

    auto bus = pub::MessageBus{};
    const auto message = DummyMessage{ .data = 10 };

    // Assert
    bus.subscribe<DummyMessage>([](DummyMessage message)
    {
        REQUIRE(message.data == 10);
    });

    // Act
    bus.publish(message);
}

TEST_CASE("Adding different message subscribers returns valid handles", "[MessageBus]")
{
    // Arrange
    struct DummyMessageOne : pub::Message
    {
    };

    struct DummyMessageTwo : pub::Message
    {
    };

    auto bus = pub::MessageBus{};

    // Act
    auto handleOne = bus.subscribe<DummyMessageOne>([](DummyMessageOne) {});
    auto handleTwo = bus.subscribe<DummyMessageTwo>([](DummyMessageTwo) {});

    // Assert
    REQUIRE(bus.validate<DummyMessageOne>(handleOne) == true);
    REQUIRE(bus.validate<DummyMessageTwo>(handleTwo) == true);
}

TEST_CASE("Validating subscribers for different messages returns false", "[MessageBus]")
{
    // Arrange
    struct DummyMessageOne : pub::Message
    {
    };

    struct DummyMessageTwo : pub::Message
    {
    };

    auto bus = pub::MessageBus{};

    // Act
    auto handleOne = bus.subscribe<DummyMessageOne>([](DummyMessageOne) {});
    auto handleTwo = bus.subscribe<DummyMessageTwo>([](DummyMessageTwo) {});

    // Assert
    REQUIRE(bus.validate<DummyMessageOne>(handleTwo) == false);
    REQUIRE(bus.validate<DummyMessageTwo>(handleOne) == false);
}

TEST_CASE("Publishing message calls subscriber", "[MessageBus]")
{
    // Arrange
    struct DummyMessage : pub::Message
    {
    };

    auto called = false;
    auto bus = pub::MessageBus{};
    const auto message = DummyMessage{};

    bus.subscribe<DummyMessage>([&called](DummyMessage) { called = true; });

    // Act
    bus.publish(message);

    // Assert
    REQUIRE(called == true);
}

TEST_CASE("Unsubscribing stops triggering calls", "[MessageBus]")
{
    // Arrange
    struct DummyMessage : pub::Message
    {
    };

    auto called = false;
    auto bus = pub::MessageBus{};
    const auto message = DummyMessage{};

    auto handle = bus.subscribe<DummyMessage>([&called](DummyMessage) { called = true; });

    // Act
    bus.unsubscribe(handle);

    // Assert
    bus.publish(message);
    REQUIRE(called == false);
}

TEST_CASE("Multiple subscribers - publishing message - all subscribers are notified", "[MessageBus]")
{
    // Arrange
    struct DummyMessage : pub::Message
    {
    };

    auto bus = pub::MessageBus{};
    const auto message = DummyMessage{};

    auto calledOne = false;
    auto calledTwo = false;

    bus.subscribe<DummyMessage>([&calledOne](DummyMessage) { calledOne = true; });
    bus.subscribe<DummyMessage>([&calledTwo](DummyMessage) { calledTwo = true; });

    // Act
    bus.publish(message);

    // Assert
    REQUIRE(calledOne == true);
    REQUIRE(calledTwo == true);
}

TEST_CASE("Multiple subscribers - unsubscribing one - all other subscribers are still notified", "[MessageBus]")
{
    // Arrange
    struct DummyMessage : pub::Message
    {
    };

    auto bus = pub::MessageBus{};
    const auto message = DummyMessage{};

    auto calledOne = false;
    auto calledTwo = false;
    auto calledThree = false;

    bus.subscribe<DummyMessage>([&calledOne](DummyMessage) { calledOne = true; });
    bus.subscribe<DummyMessage>([&calledTwo](DummyMessage) { calledTwo = true; });
    auto handle = bus.subscribe<DummyMessage>([&calledThree](DummyMessage) { calledThree = true; });

    // Act
    bus.unsubscribe(handle);

    // Assert
    bus.publish(message);
    REQUIRE(calledOne == true);
    REQUIRE(calledTwo == true);
    REQUIRE(calledThree == false);
}
