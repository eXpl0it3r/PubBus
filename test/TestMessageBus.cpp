#include "catch.hpp"
#include <PubBus/Message.hpp>
#include <PubBus/MessageBus.hpp>

TEST_CASE("Adding subscriber returns a valid SubscriberHandle", "[MessageBus]")
{
	class DummyMessage : public pub::Message
	{

	};

	pub::MessageBus bus;

	pub::SubscriberHandle handle = bus.subscribe<DummyMessage>([](DummyMessage msg) {});

	REQUIRE(bus.validate<DummyMessage>(handle) == true);
}

TEST_CASE("Adding different message subscribers returns valid handles", "[MessageBus]")
{
	class DummyMessageOne : public pub::Message
	{

	};

	class DummyMessageTwo : public pub::Message
	{

	};

	pub::MessageBus bus;

	pub::SubscriberHandle handle_one = bus.subscribe<DummyMessageOne>([](DummyMessageOne msg) {});
	pub::SubscriberHandle handle_two = bus.subscribe<DummyMessageTwo>([](DummyMessageTwo msg) {});

	REQUIRE(bus.validate<DummyMessageOne>(handle_one) == true);
	REQUIRE(bus.validate<DummyMessageTwo>(handle_two) == true);
}

TEST_CASE("Validating subscribers for different messages returns false", "[MessageBus]")
{
	class DummyMessageOne : public pub::Message
	{

	};

	class DummyMessageTwo : public pub::Message
	{

	};

	pub::MessageBus bus;

	pub::SubscriberHandle handle_one = bus.subscribe<DummyMessageOne>([](DummyMessageOne msg) {});
	pub::SubscriberHandle handle_two = bus.subscribe<DummyMessageTwo>([](DummyMessageTwo msg) {});

	REQUIRE(bus.validate<DummyMessageOne>(handle_two) == false);
	REQUIRE(bus.validate<DummyMessageTwo>(handle_one) == false);
}

TEST_CASE("Publishing message calls subscriber", "[MessageBus]")
{
	class DummyMessage : public pub::Message
	{

	};

	bool called = false;
	pub::MessageBus bus;
	DummyMessage msg;

	bus.subscribe<DummyMessage>([&called](DummyMessage msg) { called = true; });
	bus.publish(msg);

	REQUIRE(called == true);
}
