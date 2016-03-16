PubBus
======

**PubBus** is a simple implementation of a MessageBus.

Unit tests are written with the Catch test framework.

Example
-------

```c++
#include <PubBus/PubBus.hpp>
#include <iostream>

class DummyMessage : public Message
{

};

int main()
{
	MessageBus bus;
	DummyMessage msg;

	bool called = false;

	bus.subscribe<DummyMessage>([&called](DummyMessage msg) { called = true; });
	bus.publish(msg);

	std::cout << (called ? "Yes!" : "No...") << std::endl;
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
