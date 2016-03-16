#include "catch.hpp"

#include <cstddef>
#include <PubBus/SubscriberHandle.hpp>

TEST_CASE("Constructing a SubscriberHandle sets the index and id", "[SubscriberHandle]")
{
	class DummyMessage : public pub::Message
	{

	};

	pub::Message::Id id = pub::Message::id<DummyMessage>();
	std::size_t index = 10;

	pub::SubscriberHandle handle(id, index);

	REQUIRE(handle.id() == id);
	REQUIRE(handle.index() == index);
}
