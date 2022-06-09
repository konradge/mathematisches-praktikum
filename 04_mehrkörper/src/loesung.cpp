// Copyright (c) 2022, The MaPra Authors.

#include <iostream>

#include "mapra/matrix.h"
#include "mapra/unit.h"
#include "mapra/vector.h"

void RkStep(VFFunction f, real& t, RealVector& y, real& h) {}

int main() {
  auto [mass, fun, y_0, t_begin, t_end, h_0] = mapra::GetExample(1, true, true);

  return 0;
}
