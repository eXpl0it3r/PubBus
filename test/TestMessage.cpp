#include "catch.hpp"
#include <PubBus/Message.hpp>

TEST_CASE("Instances of the same Message type have the same ID", "[Message]")
{
	class DummyMessage : public Message
	{

	};

	REQUIRE(Message::id<DummyMessage>() == Message::id<DummyMessage>());
}

TEST_CASE("Instances of different Message types have different IDs", "[Message]")
{
	class DummyMessageOne : public Message
	{

	};

	class DummyMessageTwo : public Message
	{

	};

	REQUIRE(Message::id<DummyMessageOne>() != Message::id<DummyMessageTwo>());
}
