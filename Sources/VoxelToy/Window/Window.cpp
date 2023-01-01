#include <VoxelToy/Window/Window.hpp>

namespace VoxelToy
{
	Window::Window()
	{
		Init();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		//TODO: add debug ifdef
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	GLFWwindow* Window::GetWindow() const
	{
		return m_Window;
	}

	int Window::CreateWindow()
	{
		m_Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		return 1;
	}

	int Window::ShouldWindowbeClosed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::SwapBuffer() const
	{
		glfwSwapBuffers(m_Window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	int Window::Init()
	{
		if (!glfwInit())
		{
			return -1;
		}
		return 1;
	}
}// namespace VoxelToy