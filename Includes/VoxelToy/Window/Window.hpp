#pragma once
#include <GLFW/glfw3.h>

namespace VoxelToy
{
	class Window
	{
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

		[[nodiscard]] GLFWwindow* GetWindow() const;
		int CreateWindow();
		[[nodiscard]] int ShouldWindowbeClosed() const;
		void SwapBuffer() const;
		void PollEvents();

	private:
		static int Init();

	public:
		GLFWwindow* m_Window = nullptr;
		int SCR_WIDTH = 2400;
		int SCR_HEIGHT = 1200;
	};
}// namespace VoxelToy