# PubBus

**PubBus** is a simple, header-only implementation of a MessageBus.

Unit tests are written with the [Catch2](https://github.com/catchorg/Catch2) test framework.

## Example

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
			std::cout << "Important value: " << msg.important_value << "\n";
		}
	);

	bus.publish(msg);
}
```

## Test Execution

For Visual Studio I recommend to install the [Test Adapter for Catch2](https://github.com/JohnnyHendriks/TestAdapter_Catch2) and set it up to use the provided `catch.runsettings`.

## License

This software is available under 2 licenses -- choose whichever you prefer.

- Public Domain
- MIT

## Credits

* [Message Bus (GDD #3)](http://www.optank.org/2013/04/02/game-development-design-3-message-bus/) by Stefan Schindler
* [SW Message Bus](http://www.codeproject.com/Articles/723656/SW-Message-Bus) by Evgeny Zavalkovsky
* [Catch C++ Test Framework](https://github.com/philsquared/Catch) by Phil Nash
