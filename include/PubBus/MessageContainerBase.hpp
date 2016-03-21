#pragma once

#include <cstddef>

namespace pub
{
	class MessageContainerBase
	{
	public:
		virtual ~MessageContainerBase();
		virtual std::size_t size() const = 0;
		virtual void remove(std::size_t index) = 0;
		virtual bool validate(std::size_t index) const = 0;
	};

	inline MessageContainerBase::~MessageContainerBase()
	{
		
	}
}
