#include "catch.hpp"

#include<PubBus/Message.hpp>
#include<PubBus/MessageContainer.hpp>

struct DummyMessage : pub::Message
{

};

TEST_CASE("Empty container has a size of zero", "[MessageContainer]")
{
    // Arrange & Act
    auto container = pub::MessageContainer<DummyMessage>{};

    // Assert
    REQUIRE(container.size() == 0u);
}

TEST_CASE("Adding subscribers increases container size", "[MessageContainer]")
{
    // Arrange
    auto container = pub::MessageContainer<DummyMessage>{};

    // Act
    container.add([](DummyMessage){});
    container.add([](DummyMessage){});

    // Assert
    REQUIRE(container.size() == 2u);
}

TEST_CASE("Removing a non existing index does nothing", "[MessageContainer]")
{
    // Arrange
    auto container = pub::MessageContainer<DummyMessage>{};

    // Act
    container.remove(10);

    // Assert
    REQUIRE(container.size() == 0u);
}

TEST_CASE("Removing an existing index decreases the size", "[MessageContainer]")
{
    // Arrange
    auto container = pub::MessageContainer<DummyMessage>{};

    const auto index_one = container.add([](DummyMessage){});
    container.add([](DummyMessage) {});

    // Act
    container.remove(index_one);

    // Assert
    REQUIRE(container.size() == 1u);
}

TEST_CASE("Validating a non existing index returns false", "[MessageContainer]")
{
    // Arrange
    auto container = pub::MessageContainer<DummyMessage>{};

    // Act
    auto index = container.add([](DummyMessage) {});

    // Assert
    REQUIRE(container.validate(index + 1u) == false);
}

TEST_CASE("Validating an existing index returns true", "[MessageContainer]")
{
    // Arrange
    auto container = pub::MessageContainer<DummyMessage>{};

    // Act
    auto index = container.add([](DummyMessage) {});

    // Assert
    REQUIRE(container.validate(index) == true);
}

TEST_CASE("Publishing a message calls the subscriber", "[MessageContainer]")
{
    // Arrange
    auto called = false;
    auto container = pub::MessageContainer<DummyMessage>{};
    const auto message = DummyMessage{};

    container.add([&called](DummyMessage) { called = true; });

    // Act
    container.publish(message);

    // Assert
    REQUIRE(called == true);
}

TEST_CASE("A subscriber can access a published message", "[MessageContainer]")
{
    // Arrange
    struct DummyMessageInteractive : pub::Message
    {
        int test = 0;
    };

    auto called = false;
    auto container = pub::MessageContainer<DummyMessageInteractive>{};
    const auto message = DummyMessageInteractive{ .test = 10 };

    container.add([&called](const DummyMessageInteractive message) { called = (message.test == 10); });

    // Act
    container.publish(message);

    // Assert
    REQUIRE(called == true);
}
