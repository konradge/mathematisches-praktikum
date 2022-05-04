#include <functional>
#include <map>
#include <string>
#include <vector>

typedef std::function<double(double)> function_t;

typedef double (*function_ptr)(double);

typedef std::map<std::string, double> map_t;

namespace CalculateIntegral {

// std::unordered_map<double, double> function_values;
double eval_function(function_t function, map_t function_values, double value);
double newton_cotes(function_t f, double a, double b,
                    std::vector<double> weights,
                    std::vector<double> supporting_points);
double trapeze_rule(function_t f, double a, double b);
double midpoint_rule(function_t f, double a, double b);
double simpson_rule(function_t f, double a, double b);
double calculate_integral(function_t f, double a, double b, double eps);

double calculate(double (*f)(double), double a, double b, double eps);
}  // namespace CalculateIntegral