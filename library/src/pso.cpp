#include "pso.h"
#include <random>
#include <limits>
#include <algorithm>

namespace pso {

StandardPSO::StandardPSO(size_t num_particles, double w, double c1, double c2)
    : m_w(w), m_c1(c1), m_c2(c2), m_global_best_value(std::numeric_limits<double>::max()) {
    m_swarm.resize(num_particles);
}

void StandardPSO::SetParameters(double w, double c1, double c2) {
    m_w = w;
    m_c1 = c1;
    m_c2 = c2;
}

void StandardPSO::Initialize(const std::array<double, 2>& min_bound,
                             const std::array<double, 2>& max_bound,
                             ObjectiveFunction obj_func) {
    m_min_bound = min_bound;
    m_max_bound = max_bound;
    m_global_best_value = std::numeric_limits<double>::max();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist_x(min_bound[0], max_bound[0]);
    std::uniform_real_distribution<double> dist_y(min_bound[1], max_bound[1]);
    
    // Initial velocity range: [-range/2, range/2] for softer starts
    double range_x = max_bound[0] - min_bound[0];
    double range_y = max_bound[1] - min_bound[1];
    std::uniform_real_distribution<double> dist_vx(-range_x, range_x);
    std::uniform_real_distribution<double> dist_vy(-range_y, range_y);

    for (auto& particle : m_swarm) {
        particle.position = {dist_x(gen), dist_y(gen)};
        particle.velocity = {dist_vx(gen) * 0.1, dist_vy(gen) * 0.1};
        particle.best_position = particle.position;
        particle.best_value = obj_func(particle.position);

        if (particle.best_value < m_global_best_value) {
            m_global_best_value = particle.best_value;
            m_global_best_position = particle.best_position;
        }
    }
}

void StandardPSO::Step(ObjectiveFunction obj_func) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist_u(0.0, 1.0);

    for (auto& particle : m_swarm) {
        double r1 = dist_u(gen);
        double r2 = dist_u(gen);

        // Update velocity
        for (int i = 0; i < 2; ++i) {
            particle.velocity[i] = m_w * particle.velocity[i] +
                                   m_c1 * r1 * (particle.best_position[i] - particle.position[i]) +
                                   m_c2 * r2 * (m_global_best_position[i] - particle.position[i]);
                                   
            // Update position
            particle.position[i] += particle.velocity[i];
            
            // Constrain position and mirror velocity if out of bounds (simple bound handling)
            if (particle.position[i] < m_min_bound[i]) {
                particle.position[i] = m_min_bound[i];
                particle.velocity[i] = -particle.velocity[i] * 0.5;
            } else if (particle.position[i] > m_max_bound[i]) {
                particle.position[i] = m_max_bound[i];
                particle.velocity[i] = -particle.velocity[i] * 0.5;
            }
        }

        // Evaluate new position
        double current_value = obj_func(particle.position);

        // Update personal best
        if (current_value < particle.best_value) {
            particle.best_value = current_value;
            particle.best_position = particle.position;

            // Update global best
            if (current_value < m_global_best_value) {
                m_global_best_value = current_value;
                m_global_best_position = particle.position;
            }
        }
    }
}

const std::vector<Particle>& StandardPSO::GetSwarm() const {
    return m_swarm;
}

const std::array<double, 2>& StandardPSO::GetGlobalBestPosition() const {
    return m_global_best_position;
}

double StandardPSO::GetGlobalBestValue() const {
    return m_global_best_value;
}

} // namespace pso
