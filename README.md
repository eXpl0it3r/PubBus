PubBus
======

**PubBus** is a simple, header-only implementation of a MessageBus.

Unit tests are written with the Catch test framework.

Example
-------

```c++
#include <PubBus/PubBus.hpp>
#include <iostream>

struct DummyMessage : public pub::Message
{
	int important_value = 0;
};

int main()
{
	pub::MessageBus bus;
	DummyMessage msg;
	msg.important_value = 100;

	bus.subscribe<DummyMessage>(
		[](DummyMessage msg)
		{
			std::cout << "Important value: " << msg.important_value << std::endl;
		}
	);

	bus.publish(msg);
}
```

License
-------

This software is in the public domain. Where that dedication is not
recognized, you are granted a perpetual, irrevocable license to copy
and modify these files as you see fit.

Credits
-------

* [Message Bus (GDD #3)](http://www.optank.org/2013/04/02/game-development-design-3-message-bus/) by Stefan Schindler
* [SW Message Bus](http://www.codeproject.com/Articles/723656/SW-Message-Bus) by Evgeny Zavalkovsky
* [Catch C++ Test Framework](https://github.com/philsquared/Catch) by Phil Nash
