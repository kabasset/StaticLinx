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

  Box(const Stop& stop) : m_start {}, m_stop(stop) {}

  Box(const Start& start, const Stop& stop) : m_start(start), m_stop(stop) {}

  auto rank() const
  {
    return m_stop.size();
  }

  auto start(std::integral auto i) const
  {
    return m_start[i];
  }

  auto stop(std::integral auto i) const
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

template <auto... Args>
auto shape(auto... args)
{
  return Box(vec<Args...>(args...));
}

auto cube(auto radius)
{
  // return Box(vec(-args...), vec((args + 1)...));
  return Box(radius); // FIXME -radius, radius + 1
}

} // namespace Linx

#endif
