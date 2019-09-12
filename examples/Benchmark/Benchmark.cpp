#include <PubBus/PubBus.hpp>
#include <chrono>
#include <iostream>

class DummyMessage
{
public:
	DummyMessage(int x, int y)
	: m_x(x)
	, m_y(y)
	{
		
	}

	int x() const
	{
		return m_x;
	}

	int y() const
	{
		return m_y;
	}

private:
	int m_x;
	int m_y;
};

int size = 0;

void subscriber(DummyMessage msg)
{
	size += msg.x() + msg.y();
}

void subscriber2(DummyMessage msg)
{
	size -= msg.x() - msg.y();
}

int main()
{
	pub::MessageBus bus;
	bus.subscribe<DummyMessage>(subscriber);
	bus.subscribe<DummyMessage>(subscriber2);

	DummyMessage dm{ 1, 2 };

	auto t1 = std::chrono::high_resolution_clock::now();
	
	for (std::size_t i = 0; i < 1000000; ++i)
	{
		bus.publish<DummyMessage>(dm);
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	
	auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "Calculating " << size << " took me " << time_span.count() << " seconds." << std::endl;
}
