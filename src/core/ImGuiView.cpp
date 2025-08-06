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
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark();

        GLFWwindow* rawWindow = ScreenWindow::GetInstance().GetGLFWWindow();
        m_WindowWidth = ScreenWindow::GetInstance().GetWidth();
        m_WindowHeight = ScreenWindow::GetInstance().GetHeight();

        ImGui_ImplGlfw_InitForOpenGL(rawWindow, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        // Initialize the TextEditor
        m_TextEditor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
        m_TextEditor.SetText("// Write your code here...\n");
        m_TextEditor.SetShowWhitespaces(false);
}

void ImGuiView::Compile() const {
        assert(m_OnCompile && "No Compilation Callback provided");
        m_OnCompile();
}

void ImGuiView::Style() {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_ChildBg]  = ImVec4(0.12f, 0.14f, 0.17f, 1.00f);
        colors[ImGuiCol_Button]         = ImVec4(0.20f, 0.25f, 0.30f, 1.00f);
        colors[ImGuiCol_ButtonHovered]  = ImVec4(0.30f, 0.35f, 0.40f, 1.00f);
        colors[ImGuiCol_ButtonActive]   = ImVec4(0.15f, 0.20f, 0.25f, 1.00f);
        colors[ImGuiCol_Text]           = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
        colors[ImGuiCol_Border]         = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_FrameBg]        = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colors[ImGuiCol_FrameBgActive]  = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);

        style.WindowRounding = 5.3f;
        style.FrameRounding = 5.3f;
        style.ScrollbarRounding = 2.0f;
        style.GrabRounding = 2.0f;
        style.FrameBorderSize = 1.0f;
}

void ImGuiView::SetupUI(float editorWidth, float editorHeight, float editorX, float editorY) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Style();

        if (m_Font) {
                ImGui::PushFont(m_Font);
        }

        ImGui::SetNextWindowPos(ImVec2(editorX, editorY), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(editorWidth, editorHeight), ImGuiCond_Always);

        ImGui::Begin("Text Editor", nullptr,
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoTitleBar
        );

        m_TextEditor.Render("CodeEditor");

        constexpr float buttonHeight = 50.0f;
        const float buttonWidth = editorWidth - 30.0f;

        if (ImGui::Button("Compile", ImVec2(buttonWidth, buttonHeight))) {
                Compile();
        }

        ImGui::End();

        if (m_Font) {
                ImGui::PopFont();
        }
}

void ImGuiView::DrawUI() const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
