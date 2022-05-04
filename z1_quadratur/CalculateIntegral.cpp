#include "CalculateIntegral.h"

#include <cmath>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "unit.h"

umap_t function_values;

double CalculateIntegral::eval_function(double value) {
  if (function_values.find(value) == function_values.end()) {
    // Function has not been evaluated before
    function_values[value] = f(value);
  }
  return function_values[value];
}

double CalculateIntegral::newton_cotes(function_t f, double a, double b,
                                       std::vector<double> weights,
                                       std::vector<double> supporting_points) {
  // Error: Different number of weights and supporting points
  if (weights.size() != supporting_points.size()) return -1;

  double sum = 0;

  for (unsigned int i = 0; i < weights.size(); i++) {
    sum += weights[i] * f(supporting_points[i]);
  }

  return (b - a) * sum;
}

double CalculateIntegral::trapeze_rule(function_t f, double a, double b) {
  return newton_cotes(f, a, b, {0.5, 0.5}, {a, b});
}

double CalculateIntegral::midpoint_rule(function_t f, double a, double b) {
  return newton_cotes(f, a, b, {1}, {(a + b) / 2});
}

double CalculateIntegral::simpson_rule(function_t f, double a, double b) {
  return newton_cotes(f, a, b, {(double)1 / 6, (double)4 / 6, (double)1 / 6},
                      {a, (a + b) / 2, b});
}

double CalculateIntegral::calculate_integral(function_t f, double a, double b,
                                             double eps) {
  double I_M = midpoint_rule(f, a, b);
  double I_T = trapeze_rule(f, a, b);

  double error_estimator = fabs(I_M - I_T);

  if (error_estimator < eps) return simpson_rule(f, a, b);

  return calculate_integral(f, a, (a + b) / 2, eps / 2) +
         calculate_integral(f, (a + b) / 2, b, eps / 2);
}

double CalculateIntegral::calculate(double a, double b, double eps) {
  return calculate_integral(&eval_function, a, b, eps);
}