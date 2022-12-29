#pragma once

#include <glad/glad.h>

namespace VoxelToy
{
	class VertexBuffer
	{
	public:
		VertexBuffer() = delete;
		VertexBuffer(float* vertices, long size);
		[[maybe_unused]] explicit VertexBuffer(long size);
		~VertexBuffer();

		void Bind() const;
		[[maybe_unused]] static void UnBind();

	private:
		uint8_t m_NumVertexBuffer;
		unsigned int m_VertexBufferID{};
	};

	//TODO: Make Changes Here
	struct VertexBufferItems {
		unsigned int type;
		int count;
		uint8_t normalized;
		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT:
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
			default:
				assert(false);
			}
			return 0;
		}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout()
			: m_Stride(0){};

		[[nodiscard]] inline int GetStride() const
		{
			return m_Stride;
		}

		[[nodiscard]] inline const std::vector<VertexBufferItems>& GetItems() const
		{
			return m_Items;
		}

		template<typename T>
		void Push(int count)
		{
			if (std::is_same_v<T, float>)
			{
				m_Items.push_back({GL_FLOAT, count, GL_FALSE});
				m_Stride += count * VertexBufferItems::GetSizeOfType(GL_FLOAT);
			}
			else if (std::is_same<T, unsigned int>::value)
			{
				m_Items.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
				m_Stride += count * VertexBufferItems::GetSizeOfType(GL_UNSIGNED_INT);
			}
			else if (std::is_same<T, unsigned char>::value)
			{
				m_Items.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
				m_Stride += count * VertexBufferItems::GetSizeOfType(GL_UNSIGNED_BYTE);
			}
			else
			{
				assert(false);
			}
		}

	public:
		int m_Stride;
		std::vector<VertexBufferItems> m_Items;
	};
}// namespace VoxelToy