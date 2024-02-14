#pragma once

#include <PubBus/MessageContainerBase.hpp>
#include <PubBus/MessageContainer.hpp>
#include <PubBus/Message.hpp>
#include <PubBus/SubscriberHandle.hpp>
#include <functional>
#include <map>
#include <memory>

namespace pub
{
    class MessageBus
    {
    public:
        template<typename M>
        SubscriberHandle subscribe(std::function<void(const M&)> subscriber);
        void unsubscribe(SubscriberHandle& subscriber_handle);
        template<typename M>
        void publish(const M& message);
        template<typename M>
        [[nodiscard]] bool validate(SubscriberHandle handle) const;

    private:
        std::map<Message::Id, std::unique_ptr<MessageContainerBase>> m_repository;
    };

    template<typename M>
    SubscriberHandle MessageBus::subscribe(std::function<void(const M&)> subscriber)
    {
        auto repo = m_repository.find(Message::id<M>());
        auto valid = true;
        auto index = std::size_t{ 0u };

        if (repo == m_repository.end())
        {
            auto result = m_repository.insert({ Message::id<M>(), std::make_unique<MessageContainer<M>>() });
            valid = result.second;
            repo = result.first;
        }

        if (valid)
        {
            index = static_cast<MessageContainer<M>*>(repo->second.get())->add(subscriber);
        }

        return SubscriberHandle{ Message::id<M>(), index };
    }

    inline void MessageBus::unsubscribe(SubscriberHandle& subscriber_handle)
    {
        auto repo = m_repository.find(subscriber_handle.id());

        if (repo != m_repository.end())
        {
            repo->second->remove(subscriber_handle.index());
        }
    }

    template<typename M>
    void MessageBus::publish(const M& message)
    {
        auto repo = m_repository.find(Message::id<M>());

        if (repo != m_repository.end())
        {
            static_cast<MessageContainer<M>*>(repo->second.get())->publish(message);
        }
    }

    template<typename M>
    bool MessageBus::validate(SubscriberHandle handle) const
    {
        auto result = false;

        if (handle.id() != Message::id<M>())
        {
            return result;
        }

        auto repo = m_repository.find(Message::id<M>());

        if (repo != m_repository.end())
        {
            result = repo->second->validate(handle.index());
        }

        return result;
    }
}
