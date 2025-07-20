// SPDX-FileCopyrightText: Copyright (C) 2022-2025, Antoine Basset
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
class Mask {
public:

  using Domain = TDomain;

  Mask(Domain domain) : m_domain(domain) {}

  friend std::ostream& operator<<(std::ostream& os, const Mask& b)
  {
    return os << "Mask(" << b.m_domain << ")";
  }

private:

  Domain m_domain;
};

template <int Norm = 2>
constexpr auto ball(auto radius)
{
  auto box = cube(radius);
  if constexpr (Norm == -1) {
    return box;
  } else {
    return Mask(box); // FIXME draw ball
  }
}

} // namespace Linx

#endif
