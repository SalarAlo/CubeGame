#pragma once

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Utils.h>

class ScreenWindow {
public:
    ScreenWindow(unsigned int width, unsigned int height, const std::string &title);
    ~ScreenWindow();
    void Init();

    inline GLFWwindow* GetGLFWWindow() const { return m_Window; };
    inline bool ShouldClose() { return glfwWindowShouldClose(m_Window); }

private:
    void SetHints();

private:
    GLFWwindow* m_Window;   
    unsigned int m_Width;
    unsigned int m_Height;
    std::string m_Title;
};
