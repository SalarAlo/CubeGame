#include "App.h"
#include "ImGuiView.h"
#include "ScreenWindow.h"
#include <X11/Xlib.h>

void App::Run() {
        ScreenWindow::GetInstance().Init();

        int renderHeight { static_cast<int>(ScreenWindow::GetInstance().GetHeight()) };
        int renderWidth { static_cast<int>(ScreenWindow::GetInstance().GetWidth()) / 2 };

        m_Renderer.Init(renderWidth, renderHeight);
        m_Game.Init();

        ImGuiView::GetInstance().Init();

        ImGuiView::GetInstance().SetOnCompileCallback([&]() {
                this->OnCompilePressed();
        });

        while(!ScreenWindow::GetInstance().ShouldClose()) {
                ImGuiView::GetInstance().SetupUI(renderWidth, renderHeight, renderWidth);

                ScreenWindow::GetInstance().PollEvents();

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
