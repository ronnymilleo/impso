#pragma once

#include "imgui.h"
#include <string>

class IWindowInterface
{
  public:
    virtual ~IWindowInterface() = default;
    virtual void Create() = 0;
    virtual void Destroy() = 0;
    virtual void DrawContents() = 0;
    void Render()
    {
        ImGui::Begin(m_title.c_str(), &m_open, m_flags);
        DrawContents();
        ImGui::End();
    }
    virtual void Show() = 0;
    virtual void Hide() = 0;
    
    // Getters for window state
    bool IsOpen() const { return m_open; }
    const std::string& GetTitle() const { return m_title; }

  protected:
    std::string m_title;
    bool m_open = false;
    ImGuiWindowFlags m_flags = ImGuiWindowFlags_None;
};
