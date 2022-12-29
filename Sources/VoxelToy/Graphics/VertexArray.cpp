#include <VoxelToy/Graphics/VertexArray.hpp>
#include <VoxelToy/Graphics/VertexBuffer.hpp>

namespace VoxelToy
{
	VertexArray::VertexArray()
		: m_NumVertexArray(1)
	{
		glGenVertexArrays(m_NumVertexArray, &m_VertexArrayID);
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(m_NumVertexArray, &m_VertexArrayID);
	}
	void VertexArray::Bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}
	[[maybe_unused]] void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) const
	{
		this->Bind();

		const auto& items = layout.GetItems();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < items.size(); ++i)
		{
			const auto& item = items[i];
			glVertexAttribPointer(i, item.count, item.type, item.normalized, layout.GetStride(), reinterpret_cast<void*>(offset));
			glEnableVertexAttribArray(i);
			offset += item.count * VertexBufferItems::GetSizeOfType(item.type);
		}
	}

}// namespace VoxelToy