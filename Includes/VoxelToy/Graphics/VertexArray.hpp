#pragma once

namespace VoxelToy
{
	class VertexBuffer;
	class VertexBufferLayout;

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		[[maybe_unused]] static void Unbind();

		void AddVertexBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) const;

	private:
		int m_NumVertexArray;
		unsigned int m_VertexArrayID{};
	};
}// namespace VoxelToy