#include <gtest/gtest.h>
#include "pso.h"
#include "benchmarks.h"

TEST(PSOTest, SphereConvergence) {
    // 30 particles, w=0.5, c1=2.0, c2=2.0
    pso::StandardPSO optimizer(30, 0.5, 2.0, 2.0);
    
    // Bounds for initialization: [-5, 5] x [-5, 5]
    std::array<double, 2> min_bound = {-5.0, -5.0};
    std::array<double, 2> max_bound = {5.0, 5.0};
    
    optimizer.Initialize(min_bound, max_bound, pso::benchmarks::Sphere);
    
    // Run for 150 iterations
    for (int i = 0; i < 150; ++i) {
        optimizer.Step(pso::benchmarks::Sphere);
    }
    
    // Check if it got close to 0 
    EXPECT_LT(optimizer.GetGlobalBestValue(), 1e-4);
    
    auto best_pos = optimizer.GetGlobalBestPosition();
    EXPECT_NEAR(best_pos[0], 0.0, 1e-2);
    EXPECT_NEAR(best_pos[1], 0.0, 1e-2);
}

TEST(ParticleBoundsTest, InitializationWithinBounds) {
    pso::StandardPSO optimizer(100, 0.5, 2.0, 2.0);
    std::array<double, 2> min_bound = {-2.0, -1.0};
    std::array<double, 2> max_bound = {2.0, 1.0};
    
    optimizer.Initialize(min_bound, max_bound, pso::benchmarks::Sphere);
    
    for (const auto& particle : optimizer.GetSwarm()) {
        EXPECT_GE(particle.position[0], min_bound[0]);
        EXPECT_LE(particle.position[0], max_bound[0]);
        EXPECT_GE(particle.position[1], min_bound[1]);
        EXPECT_LE(particle.position[1], max_bound[1]);
    }
}
