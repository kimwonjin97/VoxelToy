#include <VoxelToy/Window/Window.hpp>
#include <VoxelToy/Graphics/Renderer.hpp>
#include <VoxelToy/Graphics/Camera.hpp>

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

	int Window::CreateWindow()
	{
		m_Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		this->SetupCallbacks();
		return 1;
	}

	int Window::ShouldWindowbeClosed()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::CursorPosCallbackfn(GLFWwindow* window, int xposIn, int yposIn)
	{
		(void)window;
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}

	void Window::SetupCallbacks()
	{

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int  height)->void {
			(void)window;
			// make sure the viewport matches the new window dimensions; note that width and
			// height will be significantly larger than specified on retina displays.
			VoxelToy::Renderer::SetViewport(0,0, width, height);
		});

		glfwSetCursorPosCallback(m_Window, CursorPosCallbackfn);


		glfwSetScrollCallback(m_Window, [this](GLFWwindow* window, double xoffset, double yoffset)
		{
			(void) window; (void) xoffset;
			fov -= static_cast<float>(yoffset);
			if (fov < 1.0f)
				fov = 1.0f;
			if (fov > 45.0f)
				fov = 45.0f;
		});

		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	int Window::ProcessInput(float deltaTime)
	{
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_Window, true);

		float cameraSpeed = static_cast<float>(2.5f * deltaTime);
		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	}
	void Window::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}
	void Window::PollEvents()
	{
		glfwPollEvents();
	}
}