#pragma once

namespace VoxelToy
{
	class Texture
	{
	public:
		Texture() = delete;
//		Texture(uint32_t width, uint32_t height);
		explicit Texture(std::string path);
		~Texture();

		void Bind(uint32_t slot = 0) const;
		void UnBind() const;

		[[nodiscard]] uint32_t getWidth() const
		{
			return m_Width;
		}
		[[nodiscard]] uint32_t getHeight() const
		{
			return m_Height;
		}
		[[nodiscard]] uint32_t get_TextureID() const
		{
			return m_TextureID[m_Index];
		}

		[[nodiscard]] const std::string& getPath() const
		{
			return m_Path;
		};

		bool operator==(const Texture& rhs) const
		{
			return m_TextureID[m_Index] == rhs.m_TextureID[m_Index];
		}
		bool operator!=(const Texture& rhs) const
		{
			return !(rhs == *this);
		}

	private:
		std::string m_Path;
		std::vector<uint32_t> m_TextureID;
		uint8_t m_NumTexture, m_Index;

		int m_Width, m_Height, nrChannels;
		unsigned char* m_LocalData;
	};
}// namespace VoxelToy