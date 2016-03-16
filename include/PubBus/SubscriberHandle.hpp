#pragma once

#include <cstddef>
#include <PubBus/Message.hpp>

namespace pub
{
	class SubscriberHandle
	{
	public:
		SubscriberHandle(Message::Id id, std::size_t index);

		Message::Id id() const;
		std::size_t index() const;

	private:
		Message::Id m_id;
		std::size_t m_index;
	};

	inline SubscriberHandle::SubscriberHandle(Message::Id id, std::size_t index)
		: m_id(id)
		, m_index(index)
	{

	}

	inline Message::Id SubscriberHandle::id() const
	{
		return m_id;
	}

	inline std::size_t SubscriberHandle::index() const
	{
		return m_index;
	}
}
