// SPDX-FileCopyrightText: Copyright (C) 2025, Antoine Basset
// SPDX-PackageSourceInfo: https://github.com/kabasset/Linx
// SPDX-License-Identifier: Apache-2.0

#ifndef LINX_DATA_VECTOR_H
#define LINX_DATA_VECTOR_H

#include "Linx/Data/Rank.h"

#include <array>
#include <concepts>
#include <iostream>
#include <utility> // integer_sequence
#include <vector>

namespace Linx {

template <typename T>
struct VectorContainerAdaptor;

template <typename T>
struct VectorContainerAdaptor<T*> {
  static constexpr int n = -1;
  using value_type = T;
  using Container = std::vector<T>;
  Container m_container;
  VectorContainerAdaptor(auto begin, auto end) : m_container(begin, end) {}
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
struct VectorContainerAdaptor<T[N]> {
  static constexpr int n = N;
  using value_type = T;
  using Container = std::array<T, N>;
  Container m_container;
  VectorContainerAdaptor(auto begin, auto end) : m_container {}
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

template <typename T, auto... Coefs>
struct VectorContainerAdaptor<std::integer_sequence<T, Coefs...>> {
  static constexpr int n = sizeof...(Coefs);
  using value_type = const T;
  using Container = void;
  VectorContainerAdaptor(auto&&...) {}
  static constexpr auto size()
  {
    return n;
  }
  value_type operator[](std::integral auto i) const
  {
    return get<Coefs...>(i);
  }

  template <auto I0 = 0, auto... Is>
  static constexpr value_type get(std::integral auto i)
  {
    return i == 0 ? I0 : get<Is...>(i - 1);
  }
};

template <>
struct VectorContainerAdaptor<void> {
  static constexpr int n = 0;
  using value_type = const int;
  using Container = void;
  VectorContainerAdaptor(auto&&...) {}
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
struct Vector {
  static constexpr auto n = VectorContainerAdaptor<T>::n;
  using value_type = typename VectorContainerAdaptor<T>::value_type;
  Vector() : m_container {} {}
  Vector(auto begin, auto end) : m_container(begin, end) {}
  auto size() const
  {
    return m_container.size();
  }
  decltype(auto) operator[](std::integral auto i) const
  {
    return m_container[i];
  }

  VectorContainerAdaptor<T> m_container;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& p)
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
auto vec(std::initializer_list<T> coefs)
{
  return Vector<T*>(coefs.begin(), coefs.end());
}

template <typename T, int N>
auto vec(T (&&coefs)[N])
{
  return Vector<T[N]>(coefs, coefs + std::size(coefs));
}

template <typename T, std::size_t N>
auto vec(const std::array<T, N>& coefs)
{
  return Vector<T[N]>(std::begin(coefs), std::end(coefs));
}

template <std::integral T0, std::integral... Ts>
auto vec(T0 coef0, Ts... coefs)
{
  return vec(std::array {coef0, T0 {coefs}...});
}

template <std::integral auto Coef0, std::integral auto... Coefs>
auto vec()
{
  using T = decltype(Coef0);
  return Vector<std::integer_sequence<T, Coef0, Coefs...>>();
}

template <Rank R, std::integral auto Coef = 0>
auto vec()
{
  using T = decltype(Coef);
  return vec_impl<Coef>(std::make_integer_sequence<T, R.n>());
}

template <std::integral auto Coef, typename T, auto... Is>
auto vec_impl(std::integer_sequence<T, Is...>)
{
  return vec<(Is, Coef)...>();
}

template <typename T = int>
auto vec_0()
{
  return Vector<>();
}

} // namespace Linx

#endif
