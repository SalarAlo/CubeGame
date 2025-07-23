#include "ImGuiView.h"

#include <functional>
#include <iostream>
#include <string>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

ImGuiView& ImGuiView::getInstance() {
        static ImGuiView imGuiView {};
        return imGuiView;
}

void ImGuiView::Init(ScreenWindow& window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();

        GLFWwindow* rawWindow = window.GetGLFWWindow();
        m_WindowWidth = window.GetWidth();
        m_WindowHeight = window.GetHeight();

        ImGui_ImplGlfw_InitForOpenGL(rawWindow, true);
        ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiView::Compile() const {
        assert(m_OnCompile && "No Compilation Callback provided");
        m_OnCompile();
}

void ImGuiView::SetupUI() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);   
        ImGui::SetNextWindowSize(ImVec2(m_WindowWidth, m_WindowHeight), ImGuiCond_Always); 
        ImGui::Begin(
                "Text Editor", 
                nullptr,     
                ImGuiWindowFlags_NoMove | 
                ImGuiWindowFlags_NoResize
        );

        ImGui::InputTextMultiline(
                "##editor", m_EditorBuffer, sizeof(m_EditorBuffer),
                ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 50)
        );

        if(ImGui::Button("Compile", ImVec2(m_WindowWidth - 15, 80))) {
                Compile();
        }

        ImGui::End();
}

void ImGuiView::DrawUI() const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

