#include "app_gui.h"
#include "imgui_layer.h"
#include "pso_control_window.h"
#include "about_window.h"
#include "window_interface.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <vector>

int main(int, char**)
{
    AppGUI app("Particle Swarm Optimization");

    if (app.Init() != 0)
    {
        spdlog::error("Failed to initialize AppGUI");
        return 1;
    }

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    std::vector<std::unique_ptr<IWindowInterface>> windows;

    auto psoWindow = std::make_unique<PSOControlWindow>();
    psoWindow->Create();
    windows.push_back(std::move(psoWindow));

    auto aboutWindow = std::make_unique<AboutWindow>();
    aboutWindow->Create();
    windows.push_back(std::move(aboutWindow));

    bool show_demo_window = false;
    bool show_menu_bar    = true;

    while (!app.ShouldClose())
    {
        app.PollEvents();

        ImGuiLayer::BeginFrame();
        ImGuiLayer::EnableDockSpace();

        if (show_menu_bar && ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                {
                    app.SetShouldClose(true);
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                bool psoOpen = windows[0]->IsOpen();
                if (ImGui::MenuItem("PSO Control", nullptr, psoOpen))
                {
                    if (psoOpen)
                        windows[0]->Hide();
                    else
                        windows[0]->Show();
                }

                bool aboutOpen = windows[1]->IsOpen();
                if (ImGui::MenuItem("About", nullptr, aboutOpen))
                {
                    if (aboutOpen)
                        windows[1]->Hide();
                    else
                        windows[1]->Show();
                }

                ImGui::Separator();

                if (ImGui::MenuItem("ImGui Demo", nullptr, show_demo_window))
                {
                    show_demo_window = !show_demo_window;
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About"))
                {
                    windows[1]->Show();
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        for (auto& window : windows)
        {
            if (window->IsOpen())
            {
                window->Render();
            }
        }

        if (show_demo_window)
        {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        ImGuiLayer::Render(app.GetWindow(), clear_color);
        ImGuiLayer::EndFrame();

        app.SwapBuffers();
    }

    for (auto& window : windows)
    {
        window->Destroy();
    }

    ImGuiLayer::Shutdown();

    return 0;
}
