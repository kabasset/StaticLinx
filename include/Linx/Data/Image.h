// SPDX-FileCopyrightText: Copyright (C) 2022-2025, Antoine Basset
// SPDX-PackageSourceInfo: https://github.com/kabasset/Linx
// SPDX-License-Identifier: Apache-2.0

#ifndef LINX_DATA_IMAGE_H
#define LINX_DATA_IMAGE_H

#include "Linx/Data/Box.h"

namespace Linx {

template <typename T, typename TDomain>
class Image {
public:

  using value_type = T;
  using Domain = TDomain;

  Image(Domain domain) : m_domain(domain) {}

  friend std::ostream& operator<<(std::ostream& os, const Image& b)
  {
    return os << b.m_domain;
  }

private:

  Domain m_domain;
};

template <typename T, typename TDomain>
auto default_initialized(TDomain domain)
{
  return Image<T, TDomain>(domain);
}

template <typename T, typename TDomain>
auto uninitialized(TDomain domain)
{
  return Image<T, TDomain>(domain);
}

} // namespace Linx

#endif
