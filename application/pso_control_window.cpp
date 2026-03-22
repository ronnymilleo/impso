#include "pso_control_window.h"
#include "benchmarks.h"
#include "implot.h"
#include <vector>

PSOControlWindow::PSOControlWindow() : m_optimizer(m_num_particles, m_w, m_c1, m_c2)
{
    m_title = "PSO Control & Visualization";
    m_open  = true;
    m_optimizer.Initialize(m_min_bound, m_max_bound, pso::benchmarks::Rastrigin);
}

void PSOControlWindow::Create()
{
}

void PSOControlWindow::Destroy()
{
}

void PSOControlWindow::Render()
{
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    IWindowInterface::Render();
}

void PSOControlWindow::Show()
{
    m_open = true;
}

void PSOControlWindow::Hide()
{
    m_open = false;
}

void PSOControlWindow::DrawContents()
{
    // Controls
    ImGui::SliderFloat("Inertia (w)", &m_w, 0.0f, 1.2f);
    ImGui::SliderFloat("Cognitive (c1)", &m_c1, 0.0f, 4.0f);
    ImGui::SliderFloat("Social (c2)", &m_c2, 0.0f, 4.0f);

    if (ImGui::Button("Apply Parameters"))
    {
        m_optimizer.SetParameters(m_w, m_c1, m_c2);
    }

    ImGui::Separator();
    ImGui::InputInt("Max Iterations", &m_max_iterations);
    if (m_max_iterations < 1)
        m_max_iterations = 1;
    ImGui::InputDouble("Tolerance", &m_tolerance);
    if (m_tolerance < 0.0)
        m_tolerance = 0.0;

    ImGui::Separator();

    if (ImGui::Button("Reset/Initialize"))
    {
        m_optimizer = pso::StandardPSO(m_num_particles, m_w, m_c1, m_c2);
        m_optimizer.Initialize(m_min_bound, m_max_bound, pso::benchmarks::Rastrigin);
        m_current_iteration = 0;
        m_is_running        = false;
    }
    ImGui::SameLine();

    bool is_done = (m_current_iteration >= m_max_iterations) || (m_optimizer.GetGlobalBestValue() <= m_tolerance);
    if (is_done && m_is_running)
    {
        m_is_running = false;
    }

    if (is_done)
        ImGui::BeginDisabled();
    if (ImGui::Button(m_is_running ? "Stop" : "Run"))
    {
        m_is_running = !m_is_running;
    }
    ImGui::SameLine();
    if (ImGui::Button("Step"))
    {
        m_optimizer.Step(pso::benchmarks::Rastrigin);
        m_current_iteration++;
    }
    if (is_done)
        ImGui::EndDisabled();

    if (m_is_running)
    {
        m_optimizer.Step(pso::benchmarks::Rastrigin);
        m_current_iteration++;
    }

    ImGui::Separator();
    const auto& gbest_pos = m_optimizer.GetGlobalBestPosition();
    ImGui::Text("Iteration: %d / %d", m_current_iteration, m_max_iterations);
    if (is_done)
    {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "Optimization Finished!");
    }
    ImGui::Text("Global Best Value: %f", m_optimizer.GetGlobalBestValue());
    ImGui::Text("Global Best Pos: (%f, %f)", gbest_pos[0], gbest_pos[1]);

    // Visualization (Very basic ImPlot)
    if (ImPlot::BeginPlot("Swarm Visualization", ImVec2(-1, -1)))
    {
        ImPlot::SetupAxes("X", "Y");
        ImPlot::SetupAxesLimits(m_min_bound[0], m_max_bound[0], m_min_bound[1], m_max_bound[1]);

        std::vector<double> xs, ys;
        const auto&         swarm = m_optimizer.GetSwarm();
        xs.reserve(swarm.size());
        ys.reserve(swarm.size());

        for (const auto& p : swarm)
        {
            xs.push_back(p.position[0]);
            ys.push_back(p.position[1]);
        }

        ImPlot::PlotScatter("Particles", xs.data(), ys.data(), xs.size());

        // Plot global best
        double g_x = gbest_pos[0];
        double g_y = gbest_pos[1];
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Cross, IMPLOT_AUTO, ImVec4(1, 0, 0, 1), IMPLOT_AUTO,
                                   ImVec4(1, 0, 0, 1));
        ImPlot::PlotScatter("Global Best", &g_x, &g_y, 1);

        ImPlot::EndPlot();
    }
}
