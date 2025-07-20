// SPDX-FileCopyrightText: Copyright (C) 2022-2025, Antoine Basset
// SPDX-PackageSourceInfo: https://github.com/kabasset/Linx
// SPDX-License-Identifier: Apache-2.0

#ifndef LINX_DATA_RANK_H
#define LINX_DATA_RANK_H

#include <array>

namespace Linx {

template <int N>
struct Rank {
  static constexpr int n = N;
};

inline namespace Literals {

template <char... Cs>
constexpr int parse_int_literal()
{
  int out = 0;
  std::array chars {Cs...};
  for (auto c : chars) {
    if (c < '0' || c > '9') {
      return -1;
    }
    out = out * 10 + (c - '0');
  }
  return out;
}

template <char... Cs>
constexpr auto operator""_D()
{
  return Rank<parse_int_literal<Cs...>()>();
}

} // namespace Literals
} // namespace Linx

#endif
