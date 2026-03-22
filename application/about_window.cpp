#include "about_window.h"

AboutWindow::AboutWindow()
{
    m_title = "About PSO";
    m_open  = false;
    m_flags = ImGuiWindowFlags_AlwaysAutoResize;
}

void AboutWindow::Create()
{
}

void AboutWindow::Destroy()
{
}

void AboutWindow::Show()
{
    m_open = true;
}

void AboutWindow::Hide()
{
    m_open = false;
}

void AboutWindow::DrawContents()
{
    ImGui::Text("Particle Swarm Optimization (PSO) in C++");
    ImGui::Separator();
    ImGui::Text("Version: 0.1.0");
    ImGui::Text("A modern C++23 validation & visualization tool.");
    ImGui::Text("Built with ImGui and ImPlot to explore PSO behaviors interactively.");
    
    ImGui::Spacing();
    ImGui::Separator();
    
    if (ImGui::Button("Close"))
    {
        m_open = false;
    }
}
