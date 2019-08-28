#include "catch.hpp"

#include<PubBus/Message.hpp>
#include<PubBus/MessageContainer.hpp>

class DummyMessage : public pub::Message
{

};

TEST_CASE("Empty container has a size of zero", "[MessageContainer]")
{
	// Arrange & Act
	pub::MessageContainer<DummyMessage> container;

	// Assert
	REQUIRE(container.size() == 0);
}

TEST_CASE("Adding subscribers increases container size", "[MessageContainer]")
{
	// Arrange
	pub::MessageContainer<DummyMessage> container;

	// Act
	container.add([](DummyMessage){});
	container.add([](DummyMessage){});

	// Assert
	REQUIRE(container.size() == 2);
}

TEST_CASE("Removing a non existing index does nothing", "[MessageContainer]")
{
	// Arrange
	pub::MessageContainer<DummyMessage> container;

	// Act
	container.remove(10);

	// Assert
	REQUIRE(container.size() == 0);
}

TEST_CASE("Removing an existing index decreases the size", "[MessageContainer]")
{
	// Arrange
	pub::MessageContainer<DummyMessage> container;

	std::size_t idx1 = container.add([](DummyMessage){});
	std::size_t idx2 = container.add([](DummyMessage) {});

	// Act
	container.remove(idx1);

	// Assert
	REQUIRE(container.size() == 1);
}

TEST_CASE("Validating a non existing index returns false", "[MessageContainer]")
{
	// Arrange
	pub::MessageContainer<DummyMessage> container;

	// Act
	std::size_t idx = container.add([](DummyMessage) {});

	// Assert
	REQUIRE(container.validate(idx + 1) == false);
}

TEST_CASE("Validating an existing index returns true", "[MessageContainer]")
{
	// Arrange
	pub::MessageContainer<DummyMessage> container;

	// Act
	std::size_t idx = container.add([](DummyMessage) {});

	// Assert
	REQUIRE(container.validate(idx) == true);
}

TEST_CASE("Publishing a message calls the subscriber", "[MessageContainer]")
{
	// Arrange
	bool called = false;
	pub::MessageContainer<DummyMessage> container;
	DummyMessage msg;
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

	bool called = false;
	pub::MessageContainer<DummyMessageInteractive> container;
	DummyMessageInteractive msg;
	msg.test = 10;
	container.add([&called](DummyMessageInteractive message) { called = (message.test == 10); });

	// Act
	container.publish(msg);

	// Assert
	REQUIRE(called == true);
}
