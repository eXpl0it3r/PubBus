#pragma once

#include <PubBus/MessageContainerBase.hpp>
#include <functional>
#include <map>

namespace pub
{
	template<typename M>
	class MessageContainer : public MessageContainerBase
	{
	public:
		~MessageContainer();

		std::size_t size() const override final;
		void remove(std::size_t index) override final;
		bool validate(std::size_t index) const override final;

		std::size_t add(std::function<void(M)> subscriber);
		void publish(M message);

	private:
		std::size_t m_index = 0;
		std::map<std::size_t, std::function<void(M)>> m_subscribers;
	};

	template <typename M>
	MessageContainer<M>::~MessageContainer()
	{
	}

	template<typename M>
	std::size_t MessageContainer<M>::size() const
	{
		return m_subscribers.size();
	}

	template<typename M>
	void MessageContainer<M>::remove(std::size_t index)
	{
		auto itr = m_subscribers.find(index);

		if (itr != m_subscribers.end())
		{
			m_subscribers.erase(itr);
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
		return m_index - 1;
	}

	template<typename M>
	void MessageContainer<M>::publish(M message)
	{
		for (auto& subscriber : m_subscribers)
			subscriber.second(message);
	}
}
