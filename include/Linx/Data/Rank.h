// SPDX-FileCopyrightText: Copyright (C) 2022-2025, Antoine Basset
// SPDX-PackageSourceInfo: https://github.com/kabasset/Linx
// SPDX-License-Identifier: Apache-2.0

#ifndef LINX_DATA_RANK_H
#define LINX_DATA_RANK_H

namespace Linx {

struct Rank {
  int n;
};

inline namespace Literals {

constexpr auto operator""_D(unsigned long long n)
{
  return Rank {static_cast<int>(n)};
}

} // namespace Literals
} // namespace Linx

#endif
