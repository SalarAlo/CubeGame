#include "App.h"
#include "ImGuiView.h"
#include "ScreenWindow.h"
#include <X11/Xlib.h>

void App::Run() {
        ScreenWindow::GetInstance().Init();

        m_Renderer.Init();
        m_Game.Init();

        ImGuiView::GetInstance().Init();

        ImGuiView::GetInstance().SetOnCompileCallback([&]() {
                this->OnCompilePressed();
        });

        while(!ScreenWindow::GetInstance().ShouldClose()) {
                ImGuiView::GetInstance().SetupUI();

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
