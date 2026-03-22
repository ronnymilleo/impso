#pragma once
#include "pso.h"
#include "window_interface.h"
#include <array>

class PSOControlWindow : public IWindowInterface
{
public:
    PSOControlWindow();
    ~PSOControlWindow() override = default;

    void Create() override;
    void Destroy() override;
    void DrawContents() override;
    void Render() override;
    void Show() override;
    void Hide() override;

private:
    int              m_num_particles = 30;
    float            m_w             = 0.5f;
    float            m_c1            = 2.0f;
    float            m_c2            = 2.0f;
    pso::StandardPSO m_optimizer;
    bool             m_is_running = false;

    // Run conditions
    int    m_current_iteration = 0;
    int    m_max_iterations    = 500;
    double m_tolerance         = 1e-6;

    // Bounds
    std::array<double, 2> m_min_bound = {-5.12, -5.12};
    std::array<double, 2> m_max_bound = {5.12, 5.12};
};
