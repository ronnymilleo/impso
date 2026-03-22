#include "benchmarks.h"
#include <cmath>
#include <numbers>

namespace pso {
namespace benchmarks {

double Sphere(const std::array<double, 2>& x) {
    return x[0] * x[0] + x[1] * x[1];
}

double Rastrigin(const std::array<double, 2>& x) {
    constexpr double A = 10.0;
    double sum = 0.0;
    for (int i = 0; i < 2; ++i) {
        sum += x[i] * x[i] - A * std::cos(2.0 * std::numbers::pi * x[i]);
    }
    return A * 2.0 + sum;
}

double Rosenbrock(const std::array<double, 2>& x) {
    double a = 1.0;
    double b = 100.0;
    return std::pow(a - x[0], 2) + b * std::pow(x[1] - x[0] * x[0], 2);
}

} // namespace benchmarks
} // namespace pso
