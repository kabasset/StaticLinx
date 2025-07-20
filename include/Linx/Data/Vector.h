// SPDX-FileCopyrightText: Copyright (C) 2022-2025, Antoine Basset
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
class VectorBase;

template <typename T>
class VectorBase<T*> {
public:

  static constexpr int n = -1;
  using value_type = T;
  using Container = std::vector<T>;

  constexpr VectorBase(auto begin, auto end) : m_container(begin, end) {}

  constexpr auto size() const
  {
    return m_container.size();
  }

  constexpr const value_type& operator[](std::integral auto i) const
  {
    return m_container[i];
  }

private:

  Container m_container;
};

template <typename T, int N>
class VectorBase<T[N]> {
public:

  static constexpr int n = N;
  using value_type = T;
  using Container = std::array<T, N>;

  constexpr VectorBase(auto begin, auto end) : m_container {}
  {
    std::copy(begin, end, m_container.data());
  }

  constexpr auto size() const
  {
    return n;
  }

  constexpr const value_type& operator[](std::integral auto i) const
  {
    return m_container[i];
  }

private:

  Container m_container;
};

template <typename T, auto... Coefs>
class VectorBase<std::integer_sequence<T, Coefs...>> {
public:

  static constexpr int n = sizeof...(Coefs);
  using value_type = const T;
  using Container = void;

  constexpr VectorBase(auto&&...) {}

  constexpr static auto size()
  {
    return n;
  }

  constexpr value_type operator[](std::integral auto i) const
  {
    return at<Coefs...>(i);
  }

private:

  template <auto I0 = 0, auto... Is>
  static constexpr value_type at(std::integral auto i)
  {
    return i == 0 ? I0 : at<Is...>(i - 1);
  }
};

template <>
class VectorBase<void> {
public:

  static constexpr int n = 0;
  using value_type = const int;
  using Container = void;

  constexpr VectorBase(auto&&...) {}

  static constexpr int size()
  {
    return 0;
  }

  constexpr int operator[](auto&&) const
  {
    return at(0);
  }

  static constexpr int at(auto&&)
  {
    return 0;
  }
};

template <typename T = void>
class Vector : public VectorBase<T> {
public:

  constexpr Vector() : VectorBase<T> {} {}

  constexpr Vector(auto begin, auto end) : VectorBase<T>(begin, end) {}
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
constexpr auto vec(std::initializer_list<T> coefs)
{
  return Vector<T*>(coefs.begin(), coefs.end());
}

template <typename T, int N>
constexpr auto vec(T (&&coefs)[N])
{
  return Vector<T[N]>(coefs, coefs + std::size(coefs));
}

template <typename T, std::size_t N>
constexpr auto vec(const std::array<T, N>& coefs)
{
  return Vector<T[N]>(std::begin(coefs), std::end(coefs));
}

template <std::integral T0, std::integral... Ts>
constexpr auto vec(T0 coef0, Ts... coefs)
{
  return vec(std::array {coef0, T0 {coefs}...});
}

template <std::integral auto Coef0, std::integral auto... Coefs>
static constexpr auto vec()
{
  using T = decltype(Coef0);
  return Vector<std::integer_sequence<T, Coef0, Coefs...>>();
}

template <typename T, auto... Is>
constexpr auto vec_impl(auto coef, std::integer_sequence<T, Is...>)
{
  return vec((Is, coef)...);
}

template <std::integral auto Coef, typename T, auto... Is>
static constexpr auto vec_impl(std::integer_sequence<T, Is...>)
{
  return vec<(Is, Coef)...>();
}

template <Rank R>
constexpr auto vec(auto coef)
{
  using T = decltype(coef);
  return vec_impl(coef, std::make_integer_sequence<T, R.n>());
}

template <Rank R, std::integral auto Coef = 0>
static constexpr auto vec()
{
  using T = decltype(Coef);
  return vec_impl<Coef>(std::make_integer_sequence<T, R.n>());
}

static constexpr auto vec()
{
  return Vector<>();
}

} // namespace Linx

#endif
