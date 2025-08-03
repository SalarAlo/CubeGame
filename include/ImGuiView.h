#pragma once

#include <string>
#include <functional>

#include "ScreenWindow.h"
#include "imgui.h"

constexpr unsigned int EDITOR_BUFFER_MAX_SIZE { 1024 * 16 };

class ImGuiView {
public:
        static ImGuiView& GetInstance();

        void Init();
        void SetupUI(float editorWidth, float editorHeight, float editorX = 0, float editorY = 0);
        void DrawUI() const;

        inline void SetOnCompileCallback(std::function<void()> onCompile) { m_OnCompile = onCompile; }
        inline std::string GetEditorText() const { return std::string(m_EditorBuffer); }
private:
        void Compile() const;
private:
        char m_EditorBuffer[EDITOR_BUFFER_MAX_SIZE] { 0 };
        unsigned int m_WindowWidth {};
        unsigned int m_WindowHeight {};
        std::function<void()> m_OnCompile {};
        ImFont* m_Font {};
};
