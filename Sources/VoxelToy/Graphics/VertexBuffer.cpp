#include <VoxelToy/Graphics/VertexBuffer.hpp>

#include <glad/glad.h>

namespace VoxelToy
{
	VertexBuffer::VertexBuffer(float* vertices, long size)
		: m_NumVertexBuffer(1)
	{
		glGenBuffers(m_NumVertexBuffer, &m_VertexBufferID);
		this->Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	[[maybe_unused]] VertexBuffer::VertexBuffer(long size)
		: m_NumVertexBuffer(1)
	{
		glGenBuffers(m_NumVertexBuffer, &m_VertexBufferID);
		this->Bind();
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(m_NumVertexBuffer, &m_VertexBufferID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VertexBufferID);
	}

	[[maybe_unused]] void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}// namespace VoxelToy