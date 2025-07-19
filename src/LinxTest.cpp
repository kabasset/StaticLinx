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
  std::cout << "{,} " << Linx::vec({1, 2, 3}) << std::endl;
  std::cout << "... " << Linx::vec(1, 2, 3) << std::endl;
  std::cout << "<T> " << Linx::vec<1, 2, 3>() << std::endl;
  std::cout << "<>  " << Linx::vec_0() << std::endl;

  std::cout << std::endl;

  std::cout << "Box(vec) " << Linx::Box(Linx::vec(1, 2, 3)) << std::endl;
  std::cout << "shape() " << Linx::shape(1, 2, 3) << std::endl;
  std::cout << "shape<> " << Linx::shape<1, 2, 3>() << std::endl;

  std::cout << std::endl;

  std::cout << "Box(vec, vec) " << Linx::Box(Linx::vec(-1, -2, -3), Linx::vec(2, 3, 4)) << std::endl;
  std::cout << "radius() " << Linx::radius(1, 2, 3) << std::endl;
  std::cout << "radius<> " << Linx::radius<1, 2, 3>() << std::endl;

  std::cout << std::endl;

  std::cout << "Image " << Linx::default_initialized<int>(Linx::shape(1, 2, 3)) << std::endl;
  std::cout << "Mask<1>() " << Linx::Mask(Linx::radius<3, 3>()).ball<1>() << std::endl;
  std::cout << "Mask() " << Linx::Mask(Linx::radius<3, 3>()).ball() << std::endl;

  using namespace Linx::Literals;
  std::cout << "ball<2_D> " << Linx::ball<3, 2_D, 1>() << std::endl;
  std::cout << "ball(2_D) " << Linx::ball<1>(Linx::vec<2_D, 3>()) << std::endl;
}
