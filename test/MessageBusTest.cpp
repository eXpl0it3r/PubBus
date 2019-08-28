#include "catch.hpp"
#include <PubBus/Message.hpp>
#include <PubBus/MessageBus.hpp>

TEST_CASE("Adding subscriber returns a valid SubscriberHandle", "[MessageBus]")
{
	// Arrange
	class DummyMessage : public pub::Message
	{

	};

	pub::MessageBus bus;

	// Act
	pub::SubscriberHandle handle = bus.subscribe<DummyMessage>([](DummyMessage msg) {});

	// Assert
	REQUIRE(bus.validate<DummyMessage>(handle) == true);
}

TEST_CASE("Adding different message subscribers returns valid handles", "[MessageBus]")
{
	// Arrange
	class DummyMessageOne : public pub::Message
	{

	};

	class DummyMessageTwo : public pub::Message
	{

	};

	pub::MessageBus bus;

	// Act
	pub::SubscriberHandle handle_one = bus.subscribe<DummyMessageOne>([](DummyMessageOne msg) {});
	pub::SubscriberHandle handle_two = bus.subscribe<DummyMessageTwo>([](DummyMessageTwo msg) {});

	// Assert
	REQUIRE(bus.validate<DummyMessageOne>(handle_one) == true);
	REQUIRE(bus.validate<DummyMessageTwo>(handle_two) == true);
}

TEST_CASE("Validating subscribers for different messages returns false", "[MessageBus]")
{
	// Arrange
	class DummyMessageOne : public pub::Message
	{

	};

	class DummyMessageTwo : public pub::Message
	{

	};

	pub::MessageBus bus;

	// Act
	pub::SubscriberHandle handle_one = bus.subscribe<DummyMessageOne>([](DummyMessageOne msg) {});
	pub::SubscriberHandle handle_two = bus.subscribe<DummyMessageTwo>([](DummyMessageTwo msg) {});

	// Assert
	REQUIRE(bus.validate<DummyMessageOne>(handle_two) == false);
	REQUIRE(bus.validate<DummyMessageTwo>(handle_one) == false);
}

TEST_CASE("Publishing message calls subscriber", "[MessageBus]")
{
	// Arrange
	class DummyMessage : public pub::Message
	{

	};

	bool called = false;
	pub::MessageBus bus;
	DummyMessage msg;

	bus.subscribe<DummyMessage>([&called](DummyMessage msg) { called = true; });

	// Act
	bus.publish(msg);

	// Assert
	REQUIRE(called == true);
}
