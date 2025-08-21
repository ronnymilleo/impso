#include "app_gui.h"
#include "imgui_layer.h"
#include <spdlog/spdlog.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_SPRINTF_IMPLEMENTATION
#include "stb_image.h"
#include "stb_sprintf.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

AppGUI::AppGUI(const std::string& title, GLint width, GLint height) : m_Title(title), m_Width(width), m_Height(height)
{
    // Default icon path - can be overridden with SetIcon()
    m_IconPath = "assets/icon.png";
}

AppGUI::~AppGUI()
{
    if (m_Window)
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}

GLint AppGUI::Init()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        spdlog::error("Failed to initialize GLFW");
        return 1;
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100 (WebGL 1.0)
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    const char* glsl_version = "#version 300 es";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    m_Window = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), m_Title.c_str(), nullptr, nullptr);
    if (m_Window == nullptr)
    {
        spdlog::error("Failed to create GLFW window");
        return 1;
    }
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1); // Enable vsync

    // Load and set window icon if available
    LoadAndSetIcon();

    ImGuiLayer::Init(m_Window, glsl_version);

    return 0;
}

void AppGUI::PollEvents()
{
    glfwPollEvents();
}

bool AppGUI::ShouldClose()
{
    return glfwWindowShouldClose(m_Window);
}

void AppGUI::SetShouldClose(bool value)
{
    glfwSetWindowShouldClose(m_Window, value);
}

void AppGUI::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

GLFWwindow* AppGUI::GetWindow() const
{
    return m_Window;
}

void AppGUI::SetIcon(const std::string& iconPath)
{
    m_IconPath = iconPath;
    if (m_Window)
    {
        LoadAndSetIcon();
    }
}

void AppGUI::LoadAndSetIcon()
{
    if (m_IconPath.empty())
    {
        spdlog::warn("No icon path specified");
        return;
    }

    // Load icon using stb_image
    int            width, height, channels;
    unsigned char* pixels = stbi_load(m_IconPath.c_str(), &width, &height, &channels, 4); // Force RGBA

    if (!pixels)
    {
        spdlog::warn("Failed to load icon from: {}", m_IconPath);
        return;
    }

    // Create GLFW image structure
    GLFWimage icon;
    icon.width  = width;
    icon.height = height;
    icon.pixels = pixels;

    // Set the window icon
    glfwSetWindowIcon(m_Window, 1, &icon);

    // Free the loaded image data
    stbi_image_free(pixels);

    spdlog::info("Window icon set successfully from: {}", m_IconPath);
}
