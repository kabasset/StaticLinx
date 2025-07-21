// SPDX-FileCopyrightText: Copyright (C) 2022-2025, Antoine Basset
// SPDX-PackageSourceInfo: https://github.com/kabasset/Linx
// SPDX-License-Identifier: Apache-2.0

#include "Linx/Data/Box.h"
#include "Linx/Data/Image.h"
#include "Linx/Data/Mask.h"
#include "Linx/Data/Rank.h"
#include "Linx/Data/Vector.h"

int main()
{
  using namespace Linx::Literals;

  std::cout << "   {...} " << Linx::vec({1, 2, 3}) << std::endl;
  std::cout << "   (...) " << Linx::vec(1, 2, 3) << std::endl;
  std::cout << "   <...> " << Linx::vec<1, 2, 3>() << std::endl;
  std::cout << "   <>    " << Linx::vec() << std::endl;
  std::cout << "<3_D>    " << Linx::vec<3_D>() << std::endl;
  std::cout << "<3_D, 1> " << Linx::vec<3_D, 1>() << std::endl;
  std::cout << "<3_D>(1) " << Linx::vec<3_D>(1) << std::endl;

  std::cout << std::endl;

  std::cout << "   Box() " << Linx::Box(Linx::vec(1, 2, 3)) << std::endl;
  std::cout << " Box({}) " << Linx::Box({1, 2, 3}) << std::endl;
  std::cout << " shape() " << Linx::shape(1, 2, 3) << std::endl;
  std::cout << " shape<> " << Linx::shape<1, 2, 3>() << std::endl;
  std::cout << "<3_D>(1) " << Linx::shape<3_D>(1) << std::endl;
  std::cout << "  box(+) " << Linx::box(Linx::vec<3_D>(1), Linx::shape<1, 2, 3>()) << std::endl;
  std::cout << "  box(-) " << Linx::box(Linx::shape(1, 2, 3), Linx::vec({2, 3, 4})) << std::endl;

  std::cout << std::endl;

  std::cout << "  Box(,) " << Linx::Box(Linx::vec(-1, -2, -3), Linx::vec(2, 3, 4)) << std::endl;
  std::cout << " Box({}) " << Linx::Box({-1, -2, -3}, {2, 3, 4}) << std::endl;
  std::cout << "  cube() " << Linx::cube(Linx::vec(1, 2, 3)) << std::endl;
  std::cout << "  cube<> " << Linx::cube(Linx::vec<1, 2, 3>()) << std::endl;

  std::cout << std::endl;

  std::cout << "   Image " << Linx::default_initialized<int>(Linx::shape(1, 2, 3)) << std::endl;
  std::cout << "ball<-1> " << Linx::ball<~0>(Linx::vec<2_D, 3>()) << std::endl;
  std::cout << " ball<1> " << Linx::ball<1>(Linx::vec<2_D>(3)) << std::endl;
}
