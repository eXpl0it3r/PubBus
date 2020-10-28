#include "catch.hpp"

#include <cstddef>
#include <PubBus/SubscriberHandle.hpp>

TEST_CASE("Constructing a SubscriberHandle sets the index and id", "[SubscriberHandle]")
{
    // Arrange
    struct DummyMessage : pub::Message
    {

    };

    auto id = pub::Message::id<DummyMessage>();
    auto index = 10u;

    // Act
    auto handle = pub::SubscriberHandle{ id, index };

    // Assert
    REQUIRE(handle.id() == id);
    REQUIRE(handle.index() == index);
}
