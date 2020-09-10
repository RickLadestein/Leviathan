#pragma once

// Based of an implementation found here (https://codereview.stackexchange.com/questions/14730/impossibly-fast-Delegate-in-c11)

#include <cassert>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace util
{

	template <typename T> class Delegate;

	template<class Ret, class ...Args>
	class Delegate<Ret(Args...)>
	{
		using FuncPtr = Ret(*)(void*, Args&&...);

		Delegate(void* const object, FuncPtr const method) noexcept :
			obj(object),
			func(method)
		{
		}

	public:

		Delegate() = default;
		Delegate(Delegate const&) = default;
		Delegate(Delegate&&) = default;
		Delegate(::std::nullptr_t const) noexcept : Delegate() { }

		template <class C, typename = typename ::std::enable_if < ::std::is_class<C>{} > ::type >
		explicit Delegate(C const* const object) noexcept :
			obj(const_cast<C*>(object))
		{
		}

		template <class C, typename =
			typename ::std::enable_if < ::std::is_class<C>{} > ::type >
			explicit Delegate(C const& object) noexcept :
			obj(const_cast<C*>(&object))
		{
		}

		template <class C>
		Delegate(C* const object, Ret(C::* const method)(Args...))
		{
			*this = From(object, method);
		}

		template <class C>
		Delegate(C* const object, Ret(C::* const method)(Args...) const)
		{
			*this = From(object, method);
		}

		template <class C>
		Delegate(C& object, Ret(C::* const method)(Args...))
		{
			*this = From(object, method);
		}

		template <class C>
		Delegate(C const& object, Ret(C::* const method)(Args...) const)
		{
			*this = From(object, method);
		}

		template<
			typename T,
			typename = typename ::std::enable_if < !::std::is_same<Delegate, typename ::std::decay<T>::type>{} > ::type
		>
			Delegate(T&& f) :
			store_(operator new(sizeof(typename ::std::decay<T>::type)),
				FunctorDeleter<typename ::std::decay<T>::type>),
			store_size_(sizeof(typename ::std::decay<T>::type))
		{
			using Functor = typename ::std::decay<T>::type;

			new (store_.get()) Functor(::std::forward<T>(f));

			obj = store_.get();

			func = FunctorStub<Functor>;

			deleter = DeleterStub<Functor>;
		}

		Delegate& operator=(Delegate const&) = default;

		Delegate& operator=(Delegate&&) = default;

		template <class C>
		Delegate& operator=(Ret(C::* const rhs)(Args...))
		{
			return *this = From(static_cast<C*>(obj), rhs);
		}

		template <class C>
		Delegate& operator=(Ret(C::* const rhs)(Args...) const)
		{
			return *this = From(static_cast<C const*>(obj), rhs);
		}

		template <
			typename T,
			typename = typename ::std::enable_if < !::std::is_same<Delegate, typename ::std::decay<T>::type>{} > ::type
		>
			Delegate& operator=(T&& f)
		{
			using Functor = typename ::std::decay<T>::type;

			if ((sizeof(Functor) > store_size_) || !store_.unique())
			{
				store_.Reset(operator new(sizeof(Functor)),
					FunctorDeleter<Functor>);

				store_size_ = sizeof(Functor);
			}
			else
			{
				deleter(store_.get());
			}

			new (store_.get()) Functor(::std::forward<T>(f));

			obj = store_.get();

			func = FunctorStub<Functor>;

			deleter = DeleterStub<Functor>;

			return *this;
		}

		template <Ret(* const funcPtr)(Args...)>
		static Delegate From() noexcept
		{
			return { nullptr, FunctionStub<funcPtr> };
		}

		template <class C, Ret(C::* const method)(Args...)>
		static Delegate From(C* const object) noexcept
		{
			return { object, MethodStub<C, method> };
		}

		template <class C, Ret(C::* const method)(Args...) const>
		static Delegate From(C const* const object) noexcept
		{
			return { const_cast<C*>(object), ConstMethodStub<C, method> };
		}

		template <class C, Ret(C::* const method)(Args...)>
		static Delegate From(C& object) noexcept
		{
			return { &object, MethodStub<C, method> };
		}

		template <class C, Ret(C::* const method)(Args...) const>
		static Delegate From(C const& object) noexcept
		{
			return { const_cast<C*>(&object), ConstMethodStub<C, method> };
		}

		template <typename T>
		static Delegate From(T&& f)
		{
			return ::std::forward<T>(f);
		}

		static Delegate From(Ret(* const funcPtr)(Args...))
		{
			return funcPtr;
		}

		template <class C>
		using member_pair =
			::std::pair<C* const, Ret(C::* const)(Args...)>;

		template <class C>
		using const_member_pair =
			::std::pair<C const* const, Ret(C::* const)(Args...) const>;

		template <class C>
		static Delegate From(C* const object,
			Ret(C::* const method)(Args...))
		{
			return member_pair<C>(object, method);
		}

		template <class C>
		static Delegate From(C const* const object,
			Ret(C::* const method)(Args...) const)
		{
			return const_member_pair<C>(object, method);
		}

		template <class C>
		static Delegate From(C& object, Ret(C::* const method)(Args...))
		{
			return member_pair<C>(&object, method);
		}

		template <class C>
		static Delegate From(C const& object,
			Ret(C::* const method)(Args...) const)
		{
			return const_member_pair<C>(&object, method);
		}

		void Reset() { func = nullptr; store_.Reset(); }

		void ResetStub() noexcept { func = nullptr; }

		void Swap(Delegate& other) noexcept { ::std::swap(*this, other); }

		bool operator==(Delegate const& rhs) const noexcept
		{
			return (obj == rhs.obj) && (func == rhs.func);
		}

		bool operator!=(Delegate const& rhs) const noexcept
		{
			return !operator==(rhs);
		}

		bool operator<(Delegate const& rhs) const noexcept
		{
			return (obj < rhs.obj) ||
				((obj == rhs.obj) && (func < rhs.func));
		}

		bool operator==(::std::nullptr_t const) const noexcept
		{
			return !func;
		}

		bool operator!=(::std::nullptr_t const) const noexcept
		{
			return func;
		}

		explicit operator bool() const noexcept { return func; }

		Ret operator()(Args... args) const
		{
			assert(func);
			return func(obj, ::std::forward<Args>(args)...);
		}

	private:
		friend struct ::std::hash<Delegate>;

		using Deleter = void(*)(void*);

		void* obj;
		FuncPtr func{};

		Deleter deleter;

		::std::shared_ptr<void> store_;
		::std::size_t store_size_;

		template <class T>
		static void FunctorDeleter(void* const p)
		{
			static_cast<T*>(p)->~T();

			operator delete(p);
		}

		template <class T>
		static void DeleterStub(void* const p)
		{
			static_cast<T*>(p)->~T();
		}

		template <Ret(*funcPtr)(Args...)>
		static Ret FunctionStub(void* const, Args&&... args)
		{
			return funcPtr(::std::forward<Args>(args)...);
		}

		template <class C, Ret(C::* method)(Args...)>
		static Ret MethodStub(void* const object, Args&&... args)
		{
			return (static_cast<C*>(object)->*method)(
				::std::forward<Args>(args)...);
		}

		template <class C, Ret(C::* method)(Args...) const>
		static Ret ConstMethodStub(void* const object, Args&&... args)
		{
			return (static_cast<C const*>(object)->*method)(
				::std::forward<Args>(args)...);
		}

		template <typename>
		struct is_member_pair : std::false_type { };

		template <class C>
		struct is_member_pair< ::std::pair<C* const,
			Ret(C::* const)(Args...)> > : std::true_type
		{
		};

		template <typename>
		struct is_const_member_pair : std::false_type { };

		template <class C>
		struct is_const_member_pair< ::std::pair<C const* const,
			Ret(C::* const)(Args...) const> > : std::true_type
		{
		};

		template <typename T>
		static typename ::std::enable_if <
			!(is_member_pair<T>::value ||
				is_const_member_pair<T>::value),
			Ret
		> ::type
			FunctorStub(void* const object, Args&&... args)
		{
			return (*static_cast<T*>(object))(::std::forward<Args>(args)...);
		}

		template <typename T>
		static typename ::std::enable_if <
			is_member_pair<T>::value ||
			is_const_member_pair<T>::value,
			Ret
		> ::type
			FunctorStub(void* const object, Args&&... args)
		{
			return (static_cast<T*>(object)->first->*
				static_cast<T*>(object)->second)(::std::forward<Args>(args)...);
		}
	};

}

namespace std
{
	template <typename Ret, typename ...Args>
	struct hash<::util::Delegate<Ret(Args...)> >
	{
		size_t operator()(::util::Delegate<Ret(Args...)> const& d) const noexcept
		{
			auto const seed(hash<void*>()(d.obj));

			return hash<typename ::util::Delegate<Ret(Args...)>::FuncPtr>()(
				d.func) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
	};
}
