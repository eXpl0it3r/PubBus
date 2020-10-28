#pragma once

#include <PubBus/MessageContainerBase.hpp>
#include <functional>
#include <map>

namespace pub
{
    template<typename M>
    class MessageContainer final : public MessageContainerBase
    {
    public:
        MessageContainer() = default;
        MessageContainer(MessageContainer&&) = default;
        MessageContainer(const MessageContainer&) = default;
        MessageContainer& operator =(MessageContainer&&) = default;
        MessageContainer& operator =(const MessageContainer&) = default;
        ~MessageContainer() = default;

        [[nodiscard]] std::size_t size() const override final;
        void remove(std::size_t index) override final;
        [[nodiscard]] bool validate(std::size_t index) const override final;

        std::size_t add(std::function<void(M)> subscriber);
        void publish(M message);

    private:
        std::size_t m_index = 0;
        std::map<std::size_t, std::function<void(M)>> m_subscribers;
    };

    template<typename M>
    std::size_t MessageContainer<M>::size() const
    {
        return m_subscribers.size();
    }

    template<typename M>
    void MessageContainer<M>::remove(std::size_t index)
    {
        auto iterator = m_subscribers.find(index);

        if (iterator != m_subscribers.end())
        {
            m_subscribers.erase(iterator);
        }
    }

    template<typename M>
    bool MessageContainer<M>::validate(std::size_t index) const
    {
        return m_subscribers.find(index) != m_subscribers.end();
    }

    template<typename M>
    std::size_t MessageContainer<M>::add(std::function<void(M)> subscriber)
    {
        m_subscribers.insert({ m_index, subscriber });
        ++m_index;
        return m_index - 1u;
    }

    template<typename M>
    void MessageContainer<M>::publish(M message)
    {
        for (auto& subscriber : m_subscribers)
        {
            subscriber.second(message);
        }
    }
}
