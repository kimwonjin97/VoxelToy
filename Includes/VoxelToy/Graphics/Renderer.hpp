#pragma once

#include <glm/glm.hpp>

namespace VoxelToy
{
	class Renderer
	{
	public:
		static void Init();
		static void SetClearColor(const glm::vec4& color);
		static void SetViewport(int x, int y, int width, int height);
		static void Clear();
		static void Draw();
	};
}// namespace VoxelToy