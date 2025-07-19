// SPDX-FileCopyrightText: Copyright (C) 2025, Antoine Basset
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

  std::cout << "Box(vec) " << Linx::Box(Linx::vec(1, 2, 3)) << std::endl;
  std::cout << " shape() " << Linx::shape(1, 2, 3) << std::endl;
  std::cout << " shape<> " << Linx::shape<1, 2, 3>() << std::endl;

  std::cout << std::endl;

  std::cout << " Box(, ) " << Linx::Box(Linx::vec(-1, -2, -3), Linx::vec(2, 3, 4)) << std::endl;
  std::cout << "radius() " << Linx::radius(1, 2, 3) << std::endl;
  std::cout << "radius<> " << Linx::radius<1, 2, 3>() << std::endl;

  std::cout << std::endl;

  std::cout << "   Image " << Linx::default_initialized<int>(Linx::shape(1, 2, 3)) << std::endl;
  std::cout << "  ball<> " << Linx::ball<3, 2_D, 1>() << std::endl;
  std::cout << "  ball() " << Linx::ball<1>(Linx::vec<2_D, 3>()) << std::endl;
}
