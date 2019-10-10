#include "catch.hpp"

#include<PubBus/Message.hpp>
#include<PubBus/MessageContainer.hpp>

class DummyMessage : public pub::Message
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

    auto index_one = container.add([](DummyMessage){});
    auto index_two = container.add([](DummyMessage) {});

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
    auto msg = DummyMessage{};

    container.add([&called](DummyMessage) { called = true; });

    // Act
    container.publish(msg);

    // Assert
    REQUIRE(called == true);
}

TEST_CASE("A subscriber can access a published message", "[MessageContainer]")
{
    // Arrange
    class DummyMessageInteractive : public pub::Message
    {
    public:
        int test = 0;
    };

    auto called = false;
    auto container = pub::MessageContainer<DummyMessageInteractive>{};
    auto msg = DummyMessageInteractive{};

    msg.test = 10;
    container.add([&called](DummyMessageInteractive message) { called = (message.test == 10); });

    // Act
    container.publish(msg);

    // Assert
    REQUIRE(called == true);
}
