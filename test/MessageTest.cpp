#include "catch.hpp"
#include <PubBus/Message.hpp>

TEST_CASE("Instances of the same Message type have the same ID", "[Message]")
{
    // Arrange
    class DummyMessage : public pub::Message
    {

    };

    // Act & Assert
    REQUIRE(pub::Message::id<DummyMessage>() == pub::Message::id<DummyMessage>());
}

TEST_CASE("Instances of different Message types have different IDs", "[Message]")
{
    // Arrange
    class DummyMessageOne : public pub::Message
    {

    };

    class DummyMessageTwo : public pub::Message
    {

    };

    // Act & Assert
    REQUIRE(pub::Message::id<DummyMessageOne>() != pub::Message::id<DummyMessageTwo>());
}
