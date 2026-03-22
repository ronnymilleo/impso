#pragma once
#include <array>

namespace pso {
namespace benchmarks {

// Sphere function: f(x) = x_0^2 + x_1^2
// Global minimum at (0, 0) is 0
double Sphere(const std::array<double, 2>& x);

// Rastrigin function
// Global minimum at (0, 0) is 0
double Rastrigin(const std::array<double, 2>& x);

// Rosenbrock function
// Global minimum at (1, 1) is 0
double Rosenbrock(const std::array<double, 2>& x);

} // namespace benchmarks
} // namespace pso
