#include "tepch.h"
#include "Platfrom/OpenGL/OpenGLWindow.h"

#include "Transcendent-Engine/core/Input.h"
#include "Transcendent-Engine/Events/KeyEvent.h"
#include "Transcendent-Engine/Events/MouseEvent.h"
#include "Transcendent-Engine/Events/ApplicationEvent.h"

namespace TE {

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		TE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	OpenGLWindow::OpenGLWindow(const WindowProps& props) {
		
		Init(props);
	}

	OpenGLWindow::~OpenGLWindow() {

		Shutdown();
	}

	void OpenGLWindow::Init(const WindowProps& props) {

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		TE_CORE_INFO("Creating Window: {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount <= 0) {
			int success = glfwInit();
			TE_CORE_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			#if defined(TE_DEBUG)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			#endif

			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			});
	}

	void OpenGLWindow::Shutdown() {

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void OpenGLWindow::OnUpdate(void) {

		glfwPollEvents();
	}

	void OpenGLWindow::SetVSync(bool enabled) {

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool OpenGLWindow::IsVSync(void) const {

		return m_Data.VSync;
	}
}
