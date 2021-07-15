# PubBus

**PubBus** is a simple, header-only implementation of a MessageBus.

Unit tests are written with the [Catch2](https://github.com/catchorg/Catch2) test framework.

**Note:** PubBus requires C++17, the examples and tests use some C++20 features

## Example

```c++
#include <PubBus/PubBus.hpp>
#include <iostream>

struct DummyMessage : pub::Message
{
    int important_value = 0;
};

int main()
{
    auto bus = pub::MessageBus{};
    const auto message = DummyMessage{ .important_value = 100 };

    bus.subscribe<DummyMessage>(
        [](const DummyMessage message)
        {
            std::cout << "Important value: " << message.important_value << "\n";
        }
    );

    bus.publish(message);
}
```

## Test Execution

For Visual Studio I recommend installing the [Test Adapter for Catch2](https://github.com/JohnnyHendriks/TestAdapter_Catch2) and set it up to use the provided `catch.runsettings`.

For CMake/CTest you can run: `ctest <build-dir>/test -S Release`

## License

This software is available under 2 licenses -- choose whichever you prefer.

- Public Domain
- MIT

## Credits

* [Message Bus (GDD #3)](http://www.optank.org/2013/04/02/game-development-design-3-message-bus/) by Stefan Schindler
* [SW Message Bus](http://www.codeproject.com/Articles/723656/SW-Message-Bus) by Evgeny Zavalkovsky
* [Catch C++ Test Framework](https://github.com/philsquared/Catch) by Phil Nash