#include "app_gui.h"
#include "imgui_layer.h"
#include "window_interface.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <vector>

// Main code
int main(int, char**)
{
    // Create app with title - the icon will be loaded automatically from assets/icon.png
    AppGUI app("Particle Swarm Optimization");

    // Optional: Set a custom icon path if needed
    // app.SetIcon("assets/icon_64.png");

    if (app.Init() != 0)
    {
        spdlog::error("Failed to initialize AppGUI");
        return 1;
    }

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Create window interfaces
    std::vector<std::unique_ptr<IWindowInterface>> windows;

    bool show_demo_window = false; // Set to false by default
    bool show_menu_bar    = true;

    while (!app.ShouldClose())
    {
        app.PollEvents();

        ImGuiLayer::BeginFrame();
        ImGuiLayer::EnableDockSpace();

        // Main menu bar
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
                    spdlog::info("Digital Control System v1.0");
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        // Render all window interfaces using a for loop
        for (auto& window : windows)
        {
            if (window->IsOpen())
            {
                window->Render();
            }
        }

        // Optional: Show ImGui demo window
        if (show_demo_window)
        {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        ImGuiLayer::Render(app.GetWindow(), clear_color);
        ImGuiLayer::EndFrame();

        app.SwapBuffers();
    }

    // Clean up windows
    for (auto& window : windows)
    {
        window->Destroy();
    }

    ImGuiLayer::Shutdown();

    return 0;
}
