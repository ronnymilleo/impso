#pragma once

#include <GLFW/glfw3.h>
#include <string>

class AppGUI
{
public:
    AppGUI() = default;
    AppGUI(const std::string& title, GLint width = 1280, GLint height = 720);
    ~AppGUI();

    GLint       Init();
    void        PollEvents();
    bool        ShouldClose();
    void        SetShouldClose(bool value);
    void        SwapBuffers();
    GLFWwindow* GetWindow() const;

    // Icon management
    void SetIcon(const std::string& iconPath);

private:
    GLFWwindow* m_Window       = nullptr;
    GLint       m_Width        = 1280;
    GLint       m_Height       = 720;
    GLint       m_BufferWidth  = 1280;
    GLint       m_BufferHeight = 720;
    std::string m_Title        = "Digital Control";
    std::string m_IconPath     = "";

    // Private icon loading method
    void LoadAndSetIcon();
};
