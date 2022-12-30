#pragma once

#include <glm/glm.hpp>


namespace VoxelToy
{
	class Renderer
	{
	public:
		static void Init();
		static void SetClearColor(const glm::vec4& color);
		static void Clear();
		static void Draw();
	};
}