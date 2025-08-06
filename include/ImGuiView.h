#pragma once

#include <string>
#include <functional>

#include "ScreenWindow.h"
#include "TextEditor.h"
#include "imgui.h"

class ImGuiView {
public:
        static ImGuiView& GetInstance();

        void Init();
        void SetupUI(float editorWidth, float editorHeight, float editorX = 0, float editorY = 0);
        void DrawUI() const;

        inline void SetOnCompileCallback(std::function<void()> onCompile) { m_OnCompile = onCompile; }
        inline std::string GetEditorText() const { return m_TextEditor.GetText(); }

private:
        void Compile() const;
        void Style();

private:
        TextEditor m_TextEditor {};
        unsigned int m_WindowWidth {};
        unsigned int m_WindowHeight {};
        std::function<void()> m_OnCompile {};
        ImFont* m_Font {};
};
