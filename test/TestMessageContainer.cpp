#include "catch.hpp"

#include<PubBus/Message.hpp>
#include<PubBus/MessageContainer.hpp>

class DummyMessage : public Message
{

};

TEST_CASE("Empty container has a size of zero", "[MessageContainer]")
{
	MessageContainer<DummyMessage> container;

	REQUIRE(container.size() == 0);
}

TEST_CASE("Adding subscribers increases container size", "[MessageContainer]")
{
	MessageContainer<DummyMessage> container;

	container.add([](DummyMessage){});
	container.add([](DummyMessage){});

	REQUIRE(container.size() == 2);
}

TEST_CASE("Removing a non existing index does nothing", "[MessageContainer]")
{
	MessageContainer<DummyMessage> container;

	container.remove(10);

	REQUIRE(container.size() == 0);
}

TEST_CASE("Removing an existing index decreases the size", "[MessageContainer]")
{
	MessageContainer<DummyMessage> container;

	std::size_t idx1 = container.add([](DummyMessage){});
	std::size_t idx2 = container.add([](DummyMessage) {});
	container.remove(idx1);

	REQUIRE(container.size() == 1);
}

TEST_CASE("Validating a non existing index returns false", "[MessageContainer]")
{
	MessageContainer<DummyMessage> container;

	std::size_t idx = container.add([](DummyMessage) {});

	REQUIRE(container.validate(idx + 1) == false);
}

TEST_CASE("Validating an existing index returns true", "[MessageContainer]")
{
	MessageContainer<DummyMessage> container;

	std::size_t idx = container.add([](DummyMessage) {});

	REQUIRE(container.validate(idx) == true);
}

TEST_CASE("Publishing a message calls the subscriber", "[MessageContainer]")
{
	bool called = false;
	MessageContainer<DummyMessage> container;
	DummyMessage msg;
	container.add([&called](DummyMessage) { called = true; });

	container.publish(msg);

	REQUIRE(called == true);
}

TEST_CASE("A subscriber can access a published message", "[MessageContainer]")
{
	class DummyMessageInteractive : public Message
	{
	public:
		int test = 0;
	};

	bool called = false;
	MessageContainer<DummyMessageInteractive> container;
	DummyMessageInteractive msg;
	msg.test = 10;
	container.add([&called](DummyMessageInteractive message) { called = (message.test == 10); });

	container.publish(msg);

	REQUIRE(called == true);
}
