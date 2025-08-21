#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>

class ImGuiLayer
{
public:
    ImGuiLayer()  = default;
    ~ImGuiLayer() = default;

    static void Init(GLFWwindow* window, const char* glsl_version);
    static void BeginFrame();
    static void EnableDockSpace();
    static void EndFrame();
    static void Render(GLFWwindow* window, ImVec4& clear_color);
    static void SetStyle();
    static void Shutdown();
};
