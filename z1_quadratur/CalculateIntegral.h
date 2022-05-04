#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

typedef double (*function_t)(double);

typedef std::unordered_map<double, double> umap_t;

namespace CalculateIntegral {
double eval_function(double value);
double newton_cotes(function_t f, double a, double b,
                    std::vector<double> weights,
                    std::vector<double> supporting_points);
double trapeze_rule(function_t f, double a, double b);
double midpoint_rule(function_t f, double a, double b);
double simpson_rule(function_t f, double a, double b);
double calculate_integral(function_t f, double a, double b, double eps);

double calculate(double a, double b, double eps);
}  // namespace CalculateIntegral