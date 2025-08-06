#pragma once

#include <tuple>
#include <type_traits>

namespace utils {
// Type trait to check if T is in Tuple
template <typename T, typename Tuple>
struct tuple_contains;

// Base case: empty tuple, T not found
template <typename T>
struct tuple_contains<T, std::tuple<>> : std::false_type {};

// Recursive case: check first type, then rest
template <typename T, typename U, typename... Ts>
struct tuple_contains<T, std::tuple<U, Ts...>>
    : std::conditional_t<std::is_same_v<T, U>, std::true_type,
                         tuple_contains<T, std::tuple<Ts...>>> {};
};