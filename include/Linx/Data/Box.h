// SPDX-FileCopyrightText: Copyright (C) 2022-2025, Antoine Basset
// SPDX-PackageSourceInfo: https://github.com/kabasset/Linx
// SPDX-License-Identifier: Apache-2.0

#ifndef LINX_DATA_BOX_H
#define LINX_DATA_BOX_H

#include "Linx/Data/Vector.h"

namespace Linx {

template <typename TStart = void, typename TStop = void>
class Box {
public:

  using Start = Vector<TStart>;
  using Stop = Vector<TStop>;

  constexpr Box(const Stop& stop) : m_start {}, m_stop(stop) {}

  constexpr Box(const Start& start, const Stop& stop) : m_start(start), m_stop(stop) {}

  constexpr auto rank() const
  {
    return m_stop.size();
  }

  constexpr auto start() const
  {
    return m_start;
  }

  constexpr auto stop() const
  {
    return m_stop;
  }

  constexpr auto start(std::integral auto i) const
  {
    return m_start[i];
  }

  constexpr auto stop(std::integral auto i) const
  {
    return m_stop[i];
  }

  friend std::ostream& operator<<(std::ostream& os, const Box& b)
  {
    return os << b.m_start << " ~ " << b.m_stop;
  }

private:

  Start m_start;
  Stop m_stop;
};

template <typename T, int N>
Box(T (&&)[N]) -> Box<void, T[N]>;

template <typename T0, int N0, typename T1, int N1>
Box(T0 (&&)[N0], T1 (&&)[N1]) -> Box<T0[N0], T1[N1]>;

template <auto... Args>
constexpr auto shape(auto... args)
{
  return Box(vec<Args...>(args...));
}

constexpr auto cube(auto radius)
{
  // return Box(vec(-args...), vec((args + 1)...));
  return Box(radius); // FIXME -radius, radius + 1
}

template <typename TStart, typename TShape>
constexpr auto box(Vector<TStart> start, Box<void, TShape> shape)
{
  return Box(start, shape.stop()); // FIXME start + shape.stop()
}

template <typename TShape, typename TStop>
constexpr auto box(Box<void, TShape> shape, Vector<TStop> stop)
{
  return Box(shape.stop(), stop); // FIXME stop - shape.stop()
}

} // namespace Linx

#endif
