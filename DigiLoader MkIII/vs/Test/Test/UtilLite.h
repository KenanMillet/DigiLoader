#ifndef _UTIL_LITE_H
#define _UTIL_LITE_H

#include <tuple>
#include <vector>

namespace UtilLite
{
	class Tuple
	{
	public:
		template <int... Iseq> struct integer_sequence {};

	private:
		template <int N, int... Iseq> struct gen_sequence : gen_sequence<N - 1, N - 1, Iseq...> {};
		template <int... Iseq> struct gen_sequence<0, Iseq...> : integer_sequence<Iseq...> {};

	public:
		template <typename T>
		static auto make_index_sequence(T&)/* -> decltype(gen_sequence<std::tuple_size<T>::value>())*/;

		template <typename T, typename F>
		static auto apply(F&, T&&)/* -> decltype(apply(f, std::forward<Tuple>(t), make_index_sequence(t)))*/;

		template <typename T, typename V>
		static void from_vArray(V&&, T&&);
		template <typename T, typename V>
		static void to_vArray(T&&, V&&);

		template <typename T, typename Arr>
		static void assign(T&, size_t, Arr&&);
		template <typename T, typename Arr>
		static void wrap(T&, size_t, Arr&&);

	private:
		template <typename T, typename F, int... N>
		static auto apply(F&, T&&, integer_sequence<N...>)/* -> decltype(f(std::get<N>(std::forward<Tuple>(t))...))*/;
		
		template <typename T, typename Arr, int... N>
		static void assign(T&, size_t, Arr&&, integer_sequence<N...>);
		template <typename T, typename Arr, int N>
		static void assign(T&, Arr&&);

		template <typename T, typename Arr, int... N>
		static void wrap(T&, size_t, Arr&&, integer_sequence<N...>);
		template <typename T, typename Arr, int N>
		static void wrap(T&, Arr&&);
	};

	template <typename T>
	auto Tuple::make_index_sequence(T&)/* -> decltype(gen_sequence<std::tuple_size<T>::value>())*/
	{
		return gen_sequence<std::tuple_size<T>::value>();
	}

	template <typename T, typename F>
	auto Tuple::apply(F& f, T&& t)/* -> decltype(apply(f, std::forward<Tuple>(t), make_index_sequence(t)))*/
	{
		return apply(f, std::forward<T>(t), make_index_sequence(t));
	}

	template <typename T, typename V>
	void Tuple::from_vArray(V&& arr, T&& t)
	{
		for(size_t i = 0; i < arr.size(); ++i) assign(std::forward<T>(t), i, std::forward<V>(arr));
	}

	template <typename T, typename V>
	void Tuple::to_vArray(T&& t, V&& arr)
	{
		for(size_t i = 0; i < arr.size(); ++i) wrap(std::forward<T>(t), i, std::forward<V>(arr));
	}

	template <typename T, typename Arr>
	void Tuple::assign(T& t, size_t n, Arr&& arr)
	{
		assign(t, n, std::forward<Arr>(arr), make_index_sequence(t));
	}

	template <typename T, typename Arr>
	void Tuple::wrap(T& t, size_t n, Arr&& arr)
	{
		wrap(t, n, std::forward<Arr>(arr), make_index_sequence(t));
	}



	template <typename T, typename F, int... N>
	auto Tuple::apply(F& f, T&& t, integer_sequence<N...>)/* -> decltype(f(std::get<N>(std::forward<T>(t))...))*/
	{
		return f(std::get<N>(std::forward<T>(t))...);
	}

	template <typename T, typename Arr, int... N>
	void Tuple::assign(T& t, size_t n, Arr&& arr, integer_sequence<N...>)
	{
		typedef void(*FT)(T&, Arr&&);
		static const FT fa[] = { &assign<T, Arr, N>... };
		fa[n](t, std::forward<Arr>(arr));
	}

	template <typename T, typename Arr, int N>
	void Tuple::assign(T& t, Arr&& arr)
	{
		typedef std::tuple_element<N, T>::type Type;
		std::get<N>(t) = *((Type*)arr[N]);
	}

	template <typename T, typename Arr, int... N>
	void Tuple::wrap(T& t, size_t n, Arr&& arr, integer_sequence<N...>)
	{
		typedef void(*FT)(T&, Arr&&);
		static const FT fa[] = { &wrap<T, Arr, N>... };
		fa[n](t, std::forward<Arr>(arr));
	}

	template <typename T, typename Arr, int N>
	void Tuple::wrap(T& t, Arr&& arr)
	{
		arr[N] = &(std::get<N>(t));
	}
}

#endif