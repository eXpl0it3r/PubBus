#pragma once

#include <typeindex>

namespace pub
{
    struct Message
    {
        using Id = std::type_index;

        template<typename T>
        static Id id();
    };

    template<typename T>
    Message::Id Message::id()
    {
        return std::type_index{ typeid(T) };
    }
}
