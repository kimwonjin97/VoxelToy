#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace VoxelToy
{
	class Window
	{
	class Camera;
	public:
		Window();
		~Window();

		const unsigned int GetScrWidth() const
		{
			return SCR_WIDTH;
		}
		const unsigned int GetScrHeight() const
		{
			return SCR_HEIGHT;
		}

		int CreateWindow();

		int ShouldWindowbeClosed();

		int ProcessInput(float deltaTime);

		void SwapBuffer();

		void PollEvents();

	private:
		void CursorPosCallbackfn(GLFWwindow* window, int xposIn, int yposIn);

		void SetupCallbacks();
		static int Init()
		{
			if (!glfwInit())
			{
				return -1;
			}
		}


	public:
		GLFWwindow* m_Window = nullptr;
		int SCR_WIDTH = 2400;
		int SCR_HEIGHT = 1200;
		glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

		float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
		float pitch =  0.0f;
		float lastX =  800.0f / 2.0f;
		float lastY =  600.0f / 2.0f;
		float fov   =  45.0f;
	private:
		bool firstMouse = true;
	};
}// namespace VoxelToy