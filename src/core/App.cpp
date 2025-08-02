#include "App.h"
#include "ImGuiView.h"
#include "ScreenWindow.h"
#include <X11/Xlib.h>

void App::Run() {
        auto& window = ScreenWindow::GetInstance();
        window.Init();

        const int renderHeight { static_cast<int>(window.GetHeight()) };
        const int renderWidth { static_cast<int>(window.GetWidth()) / 2 };

        m_Renderer.Init(renderWidth, renderHeight);
        m_Game.Init();

        ImGuiView::GetInstance().Init();

        ImGuiView::GetInstance().SetOnCompileCallback([&]() {
                this->OnCompilePressed();
        });

        while(!window.ShouldClose()) {
                window.PollEvents();

                ImGuiView::GetInstance().SetupUI(renderWidth, renderHeight, renderWidth);

                m_Renderer.BeginFrame();

                m_Game.Render(m_Renderer);

                ImGuiView::GetInstance().DrawUI();

                m_Renderer.EndFrame();
        }

}

void App::OnCompilePressed() {
        const std::string& source = ImGuiView::GetInstance().GetEditorText();

        m_Executor.SetSourceCode(source);

        m_Game.RebuildChunk(m_Executor);
}
