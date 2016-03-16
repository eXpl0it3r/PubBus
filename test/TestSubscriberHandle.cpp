#include "catch.hpp"

#include <cstddef>
#include <PubBus/SubscriberHandle.hpp>

TEST_CASE("Constructing a SubscriberHandle sets the index and id", "[SubscriberHandle]")
{
	class DummyMessage : public Message
	{

	};

	Message::Id id = Message::id<DummyMessage>();
	std::size_t index = 10;

	SubscriberHandle handle(id, index);

	REQUIRE(handle.id() == id);
	REQUIRE(handle.index() == index);
}
