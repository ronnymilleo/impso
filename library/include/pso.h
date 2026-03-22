#pragma once

#include <vector>
#include <array>
#include <functional>

namespace pso {

struct Particle {
    std::array<double, 2> position;
    std::array<double, 2> velocity;
    std::array<double, 2> best_position;
    double best_value;
};

class StandardPSO {
public:
    using ObjectiveFunction = std::function<double(const std::array<double, 2>&)>;

    StandardPSO(size_t num_particles, double w, double c1, double c2);

    // Initialize particles bounded between [min_bound, max_bound]
    void Initialize(const std::array<double, 2>& min_bound, 
                    const std::array<double, 2>& max_bound, 
                    ObjectiveFunction obj_func);

    // Perform a single iteration of the algorithm
    void Step(ObjectiveFunction obj_func);

    // Getters
    const std::vector<Particle>& GetSwarm() const;
    const std::array<double, 2>& GetGlobalBestPosition() const;
    double GetGlobalBestValue() const;
    
    // Setters
    void SetParameters(double w, double c1, double c2);

private:
    std::vector<Particle> m_swarm;
    std::array<double, 2> m_global_best_position;
    double m_global_best_value;
    
    double m_w, m_c1, m_c2;
    
    // Ensure bounds hold
    std::array<double, 2> m_min_bound;
    std::array<double, 2> m_max_bound;
};

} // namespace pso
