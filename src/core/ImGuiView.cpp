#include "ImGuiView.h"
#include "ScreenWindow.h"

#include <functional>
#include <iostream>
#include <string>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

ImGuiView& ImGuiView::GetInstance() {
        static ImGuiView imGuiView {};
        return imGuiView;
}

void ImGuiView::Init() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();

        
        GLFWwindow* rawWindow = ScreenWindow::GetInstance().GetGLFWWindow();
        m_WindowWidth = ScreenWindow::GetInstance().GetWidth();
        m_WindowHeight = ScreenWindow::GetInstance().GetHeight();

        ImGui_ImplGlfw_InitForOpenGL(rawWindow, true);
        ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiView::Compile() const {
        assert(m_OnCompile && "No Compilation Callback provided");
        m_OnCompile();
}


void ImGuiView::SetupUI(float editorWidth, float editorHeight, float editorX, float editorY) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(editorX, editorY), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(editorWidth, editorHeight), ImGuiCond_Always);

        ImGui::Begin("Text Editor", nullptr,
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove   |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoTitleBar
        );


        constexpr unsigned int initialLinesAmt { 40 };

        ImGui::InputTextMultiline(
                "##editor", 
                m_EditorBuffer, sizeof(m_EditorBuffer),
                ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * initialLinesAmt)
        );

        constexpr int buttonHeight { 50 };
        const int buttonPaddingLR { -15 };
        const int buttonWidth { static_cast<int>(editorWidth + buttonPaddingLR) };

        if (ImGui::Button("Compile", ImVec2(buttonWidth, buttonHeight))) {
                Compile();
        }

        ImGui::End();
}



void ImGuiView::DrawUI() const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

