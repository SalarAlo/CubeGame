
#include <ScreenWindow.h>

#include <cassert>

static constexpr int WINDOW_HEIGHT { 700 };
static constexpr int WINDOW_WIDTH { 1000 };
static const std::string WINDOW_TITLE { "Replicube" };

ScreenWindow::ScreenWindow(
    unsigned int width,
    unsigned int height,
    const std::string& title)
    : m_Width(width)
    , m_Height(height)
    , m_Title(title) {
}

ScreenWindow::~ScreenWindow() {
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}


ScreenWindow& ScreenWindow::GetInstance() {
        static ScreenWindow window { WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE };
        return window;
}

void ScreenWindow::Init() {
	glfwInit();
	SetHints();

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

	if (!m_Window) {
		glfwTerminate();
		assert(false && "Failed to create GLFW window");
		return;
	}

	glfwMakeContextCurrent(m_Window);
	loadWithGlad();

	glEnable(GL_DEPTH_TEST);
        glEnable(GL_SCISSOR_TEST);
}

void ScreenWindow::SetHints() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
