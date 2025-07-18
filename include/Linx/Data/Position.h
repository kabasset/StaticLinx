// SPDX-FileCopyrightText: Copyright (C) 2025, Antoine Basset
// SPDX-PackageSourceInfo: https://github.com/kabasset/Linx
// SPDX-License-Identifier: Apache-2.0

#ifndef LINX_DATA_POSITION_H
#define LINX_DATA_POSITION_H

#include "Linx/Data/Rank.h"

#include <array>
#include <concepts>
#include <iostream>
#include <utility> // integer_sequence
#include <vector>

namespace Linx {

template <typename T>
struct PositionContainerAdaptor;

template <typename T>
struct PositionContainerAdaptor<T*> {
  static constexpr int n = -1;
  using value_type = T;
  using Container = std::vector<T>;
  Container m_container;
  PositionContainerAdaptor(auto begin, auto end) : m_container(begin, end) {}
  auto size() const
  {
    return m_container.size();
  }
  const value_type& operator[](std::integral auto i) const
  {
    return m_container[i];
  }
};

template <typename T, int N>
struct PositionContainerAdaptor<T[N]> {
  static constexpr int n = N;
  using value_type = T;
  using Container = std::array<T, N>;
  Container m_container;
  PositionContainerAdaptor(auto begin, auto end) : m_container {}
  {
    std::copy(begin, end, m_container.data());
  }
  auto size() const
  {
    return n;
  }
  const value_type& operator[](std::integral auto i) const
  {
    return m_container[i];
  }
};

template <typename T, auto... Is>
struct PositionContainerAdaptor<std::integer_sequence<T, Is...>> {
  static constexpr int n = sizeof...(Is);
  using value_type = const T;
  using Container = void;
  PositionContainerAdaptor(auto&&...) {}
  static constexpr auto size()
  {
    return n;
  }
  value_type operator[](std::integral auto i) const
  {
    return get<Is...>(i);
  }

  template <auto J0 = 0, auto... Js>
  static constexpr value_type get(std::integral auto i)
  {
    return i == 0 ? J0 : get<Js...>(i - 1);
  }
};

template <>
struct PositionContainerAdaptor<void> {
  static constexpr int n = 0;
  using value_type = const int;
  using Container = void;
  PositionContainerAdaptor(auto&&...) {}
  int size() const
  {
    return 0;
  }
  constexpr int operator[](auto&&) const
  {
    return 0;
  }
};

template <typename T = void>
struct Position {
  static constexpr auto n = PositionContainerAdaptor<T>::n;
  using value_type = typename PositionContainerAdaptor<T>::value_type;
  Position() : m_container {} {}
  Position(auto begin, auto end) : m_container(begin, end) {}
  auto size() const
  {
    return m_container.size();
  }
  decltype(auto) operator[](std::integral auto i) const
  {
    return m_container[i];
  }

  PositionContainerAdaptor<T> m_container;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Position<T>& p)
{
  if (p.size() == 0) {
    return os << "O";
  }

  os << "[" << p[0];
  for (int i = 1; i < p.size(); ++i) {
    os << ", " << p[i];
  }
  return os << "]";
}

template <typename T>
auto at(std::initializer_list<T> position)
{
  return Position<T*>(position.begin(), position.end());
}

template <typename T, int N>
auto at(T (&&position)[N])
{
  return Position<T[N]>(position, position + std::size(position));
}

template <typename T, std::size_t N>
auto at(const std::array<T, N>& position)
{
  return Position<T[N]>(std::begin(position), std::end(position));
}

template <std::integral T0, std::integral... Ts>
auto at(T0 i0, Ts... is)
{
  return at(std::array {i0, T0 {is}...});
}

template <std::integral auto I0, std::integral auto... Is>
auto at()
{
  using T = decltype(I0);
  return Position<std::integer_sequence<T, I0, Is...>>();
}

template <std::integral auto I, Rank R>
auto at()
{
  using T = decltype(I);
  return at_impl<I>(std::make_integer_sequence<T, R.n>());
}

template <std::integral auto I, typename T, auto... Is>
auto at_impl(std::integer_sequence<T, Is...>)
{
  return at<(I + Is * 0)...>();
}

consteval auto as_consteval(auto in)
{
  return in;
}

template <typename T = int>
auto origin()
{
  return Position<>();
}

} // namespace Linx

#endif
