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
  Domain m_domain;
};

template <typename TDomain>
std::ostream& operator<<(std::ostream& os, const Mask<TDomain>& b)
{
  return os << "Mask(" << b.m_domain << ")";
}

template <int Norm = 2>
constexpr auto ball(auto radius)
{
  auto box = Box(radius); // FIXME -radius, radius + 1
  if constexpr (Norm == -1) {
    return box;
  } else {
    return Mask(Box(radius)); // FIXME draw box
  }
}

} // namespace Linx

#endif
