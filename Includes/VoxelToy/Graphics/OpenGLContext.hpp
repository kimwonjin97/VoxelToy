#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace VoxelToy
{
	class OpenGLContext
	{
	public:
		explicit OpenGLContext(GLFWwindow* window)
			: m_Window(window){};
		~OpenGLContext() = default;
		;

		void Init() const
		{
			glfwMakeContextCurrent(m_Window);
			if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				assert(false);
			}
		}

	public:
		GLFWwindow* m_Window;
	};
}// namespace VoxelToy