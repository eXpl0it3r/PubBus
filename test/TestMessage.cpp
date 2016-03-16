#include "catch.hpp"
#include <PubBus/Message.hpp>

TEST_CASE("Instances of the same Message type have the same ID", "[Message]")
{
	class DummyMessage : public pub::Message
	{

	};

	REQUIRE(pub::Message::id<DummyMessage>() == pub::Message::id<DummyMessage>());
}

TEST_CASE("Instances of different Message types have different IDs", "[Message]")
{
	class DummyMessageOne : public pub::Message
	{

	};

	class DummyMessageTwo : public pub::Message
	{

	};

	REQUIRE(pub::Message::id<DummyMessageOne>() != pub::Message::id<DummyMessageTwo>());
}
