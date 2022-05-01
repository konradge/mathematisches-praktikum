#include <functional>
#include <unordered_map>
#include <vector>

namespace CalculateIntegral {
typedef std::function<double(double)> function_t;
std::unordered_map<double, double> function_values;
double eval_function(function_t function,
                     std::unordered_map<double, double> function_values,
                     double value);
double newton_cotes(function_t f, double a, double b,
                    std::vector<double> weights,
                    std::vector<double> supporting_points);
double trapeze_rule(function_t f, double a, double b);
double midpoint_rule(function_t f, double a, double b);
double simpson_rule(function_t f, double a, double b);
double calculate_integral(function_t f, double a, double b, double eps);

double calculate(function_t f, double a, double b, double eps);
}  // namespace CalculateIntegral