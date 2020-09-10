#pragma once

#include "Delegate.h"

#include <unordered_set>

namespace util
{

	// usage: w->keyboard->OnKeyPressedCallback += util::Delegate<KeyPressFunc>(r, &Random::OnKeyPressed);
	// literal Mutlidelegate class member += util::Delegate<delegate function>(object handle, pointer to function);
	template <typename T> class MultiDelegate;

	template<typename...Args>
	class MultiDelegate<void(Args...)>
	{
	public:

		MultiDelegate() = default;
		MultiDelegate(MultiDelegate const&) = default;
		MultiDelegate(MultiDelegate&&) = default;

		inline void Add(const Delegate<void(Args...)>& del)
		{
			delegates.emplace(del);
		}

		inline void Remove(const Delegate<void(Args...)>& del)
		{
			delegates.erase(del);
		}

		inline void Broadcast(Args... args) const
		{
			for (auto del : delegates)
			{
				del(args...);
			}
		}

		inline void operator+=(const Delegate<void(Args...)>& del)
		{
			Add(del);
		}

		inline void operator-=(const Delegate<void(Args...)>& del)
		{
			Remove(del);
		}

	private:

		std::unordered_set<Delegate<void(Args...)>> delegates;
	};
}