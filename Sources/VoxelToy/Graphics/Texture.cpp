#include <VoxelToy/Graphics/Texture.hpp>

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>
#include <utility>

namespace VoxelToy
{
	Texture::Texture(std::string path /*, int m_Index*/)
		: m_Path(std::move(path)), m_NumTexture(1), m_Index(0)
	{
		//TODO: modify m_Index if m_NumberTexture is > 1
		m_TextureID.reserve(m_NumTexture);
		glGenTextures(1, &m_TextureID[m_Index]);
		glBindTexture(GL_TEXTURE_2D, m_TextureID[m_Index]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_set_flip_vertically_on_load(true);

		m_LocalData = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &nrChannels, 0);
		if (m_LocalData)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalData);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(m_LocalData);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(m_NumTexture, &m_TextureID[0]);
	}

	void Texture::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID[m_Index]);
	}

	void Texture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}