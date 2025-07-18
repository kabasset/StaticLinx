// SPDX-FileCopyrightText: Copyright (C) 2025, Antoine Basset
// SPDX-PackageSourceInfo: https://github.com/kabasset/Linx
// SPDX-License-Identifier: Apache-2.0

#include "Linx/Data/Box.h"
#include "Linx/Data/Image.h"
#include "Linx/Data/Mask.h"
#include "Linx/Data/Position.h"
#include "Linx/Data/Rank.h"

int main()
{
  std::cout << "{,} " << Linx::at({1, 2, 3}) << std::endl;
  std::cout << "... " << Linx::at(1, 2, 3) << std::endl;
  std::cout << "<T> " << Linx::at<1, 2, 3>() << std::endl;
  std::cout << "<>  " << Linx::origin() << std::endl;

  std::cout << std::endl;

  std::cout << "Box(at) " << Linx::Box(Linx::at(1, 2, 3)) << std::endl;
  std::cout << "shape() " << Linx::shape(1, 2, 3) << std::endl;
  std::cout << "shape<> " << Linx::shape<1, 2, 3>() << std::endl;

  std::cout << std::endl;

  std::cout << "Box(at, at) " << Linx::Box(Linx::at(-1, -2, -3), Linx::at(2, 3, 4)) << std::endl;
  std::cout << "radius() " << Linx::radius(1, 2, 3) << std::endl;
  std::cout << "radius<> " << Linx::radius<1, 2, 3>() << std::endl;

  std::cout << std::endl;

  std::cout << "Image " << Linx::default_initialized<int>(Linx::shape(1, 2, 3)) << std::endl;
  std::cout << "Mask<1>() " << Linx::Mask(Linx::radius<3, 3>()).ball<1>() << std::endl;
  std::cout << "Mask() " << Linx::Mask(Linx::radius<3, 3>()).ball() << std::endl;
  std::cout << "ball<1> " << Linx::ball<1>(Linx::radius<3, 3>()) << std::endl;
  std::cout << "ball " << Linx::ball(Linx::radius<3, 3>()) << std::endl;

  using namespace Linx::Literals;
  std::cout << "2_D " << Linx::ball<3, 2_D, 1>() << std::endl;
}
