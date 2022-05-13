// Copyright (c) 2022, The MaPra Authors.

#ifndef UNIT_H_
#define UNIT_H_

#include <cstdint>
#include <tuple>

#include "matrix.h"
#include "vector.h"

namespace mapra {

inline constexpr int kNumExamples = 9;

std::tuple<Matrix, Vector, double> GetExample(int ex_id);

void CheckSolution(const Vector& eig_vec, double eig_val,
                   std::int64_t iterations);

}  // namespace mapra

#endif  // UNIT_H_
