#pragma once
#include <cinttypes>
#include <type_traits>

#include <utility>
#include <tuple>

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

#include <set>
#include <map>

#include <unordered_set>
#include <unordered_map>

namespace ez::intern {
	template<typename T>
	struct is_complex: std::false_type {};

	template<typename T>
	struct is_complex<std::complex<T>>: std::true_type {};

	template<typename T, typename = int>
	struct is_container : std::false_type {};

	template<typename T>
	struct is_container<T, decltype(
		std::declval<typename T::value_type>(), // Check if it has value_type defined
		std::declval<typename T::iterator>(), // Check if it has iterator defined
		std::declval<typename T::const_iterator>(), // Check if it has const_iterator defined
		std::declval<T>().begin(),
		std::declval<T>().end(),
		std::declval<T>().size(),
		0 // Make decltype return int
		)> : std::true_type {};


	template<typename T, typename = int>
	struct type_supported : std::false_type {};

	template<typename T>
	struct type_supported<T, std::enable_if_t<std::is_arithmetic_v<T>, int>> : std::true_type {};

	template<>
	struct type_supported<bool, int> : std::true_type {};

	template<>
	struct type_supported<void*, int> : std::true_type {};

	// ---   misc   ---

	// std::pair
	template<typename A, typename B>
	struct type_supported<std::pair<A, B>, std::enable_if_t<type_supported<A>::value && type_supported<B>::value, int>> : std::true_type {
		
	};

	// std::tuple
	template<typename ... Ts>
	struct type_supported<
		std::tuple<Ts...>, 
		std::enable_if_t<
			std::conjunction_v<
				type_supported<Ts>...
				>
			, int>
		> : std::true_type {};


	// ---   Sequence containers   ---

	// std::array
	template<typename T, size_t N>
	struct type_supported<std::array<T, N>, std::enable_if_t<type_supported<T>::value, int>> : std::true_type {
		
	};

	// std::vector
	template<typename T, typename Allocator>
	struct type_supported<std::vector<T, Allocator>, std::enable_if_t<type_supported<T>::value, int>> : std::true_type {
		
	};

	// std::deque
	template<typename T, typename Allocator>
	struct type_supported<std::deque<T, Allocator>, std::enable_if_t<type_supported<T>::value, int>> : std::true_type {
		
	};

	// std::forward_list
	template<typename T, typename Allocator>
	struct type_supported<std::forward_list<T, Allocator>, std::enable_if_t<type_supported<T>::value, int>> : std::true_type {
		
	};

	// std::list
	template<typename T, typename Allocator>
	struct type_supported<std::list<T, Allocator>, std::enable_if_t<type_supported<T>::value, int>> : std::true_type {

	};

	// ---   Associative containers   ---

	// std::set
	template<typename T, typename Compare, typename Allocator>
	struct type_supported<std::set<T, Compare, Allocator>, std::enable_if_t<type_supported<T>::value, int>> : std::true_type {
		
	};

	// std::multiset
	template<typename T, typename Compare, typename Allocator>
	struct type_supported<std::multiset<T, Compare, Allocator>, std::enable_if_t<type_supported<T>::value, int>> : std::true_type {

	};

	// std::unordered_set
	template<typename T, typename Compare, typename Allocator>
	struct type_supported<std::unordered_set<T, Compare, Allocator>, std::enable_if_t<type_supported<T>::value, int>> : std::true_type {

	};

	// std::unordered_multiset
	template<typename T, typename Compare, typename Allocator>
	struct type_supported<std::unordered_multiset<T, Compare, Allocator>, std::enable_if_t<type_supported<T>::value, int>> : std::true_type {

	};

	// std::map
	template<typename Key, typename T, typename Compare, typename Allocator>
	struct type_supported<std::map<Key, T, Compare, Allocator>, std::enable_if_t<type_supported<Key>::value && type_supported<T>::value, int>>: std::true_type {
		
	};

	// std::multimap
	template<typename Key, typename T, typename Compare, typename Allocator>
	struct type_supported<std::multimap<Key, T, Compare, Allocator>, std::enable_if_t<type_supported<Key>::value&& type_supported<T>::value, int>> : std::true_type {

	};

	// std::unordered_map
	template<typename Key, typename T, typename Compare, typename Allocator>
	struct type_supported<std::unordered_map<Key, T, Compare, Allocator>, std::enable_if_t<type_supported<Key>::value&& type_supported<T>::value, int>> : std::true_type {

	};

	// std::unordered_multimap
	template<typename Key, typename T, typename Compare, typename Allocator>
	struct type_supported<std::unordered_multimap<Key, T, Compare, Allocator>, std::enable_if_t<type_supported<Key>::value&& type_supported<T>::value, int>> : std::true_type {

	};
}