// SPDX-FileCopyrightText: Copyright (C) 2025, Antoine Basset
// SPDX-PackageSourceInfo: https://github.com/kabasset/Linx
// SPDX-License-Identifier: Apache-2.0

#ifndef LINX_DATA_MASK_H
#define LINX_DATA_MASK_H

#include "Linx/Data/Box.h"
#include "Linx/Data/Rank.h"
#include "Linx/Data/Vector.h"

#include <limits>

namespace Linx {

template <typename TDomain>
struct Mask {
  using Domain = TDomain;
  Mask(Domain domain) : m_domain(domain) {}
  template <int Norm = 2>
  Mask& ball()
  {
    return ball<Norm>(incircle());
  }
  template <int Norm = 2>
  Mask& ball(double radius)
  {
    return *this;
  }

  int incircle() const
  {
    int out = std::numeric_limits<int>::max();
    for (int i = 0; i < m_domain.rank(); ++i) {
      out = std::min(out, -m_domain.start(i));
      out = std::min(out, m_domain.stop(i) - 1);
    }
    return out;
  }
  Domain m_domain;
};

template <typename TDomain>
std::ostream& operator<<(std::ostream& os, const Mask<TDomain>& b)
{
  return os << b.m_domain;
}

template <int Radius, Rank R, int Norm = 2>
constexpr auto ball()
{
  return Mask(Box(vec<R, Radius>())).template ball<Norm>(); // FIXME
}

template <int Norm = 2>
constexpr auto ball(auto radius)
{
  return Mask(Box(radius)).template ball<Norm>();
}

} // namespace Linx

#endif
