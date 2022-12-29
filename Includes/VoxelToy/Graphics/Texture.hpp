#pragma once

namespace VoxelToy
{
	class Texture
	{
	public:
		Texture() = delete;
		explicit Texture(std::string path);
		~Texture();

		void Bind(uint32_t slot = 0) const;
		[[maybe_unused]] static void UnBind() ;

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
			return m_TextureID;
		}

		[[nodiscard]] const std::string& getPath() const
		{
			return m_Path;
		};

		bool operator==(const Texture& rhs) const
		{
			return m_TextureID == rhs.m_TextureID;
		}
		bool operator!=(const Texture& rhs) const
		{
			return !(rhs == *this);
		}

	private:
		std::string m_Path;
		uint8_t m_NumTexture, m_Index;
		//		std::vector<uint32_t> m_TextureID;
		uint32_t m_TextureID{};

		int m_Width{}, m_Height{}, nrChannels{};
		unsigned char* m_LocalData;
	};
}// namespace VoxelToy