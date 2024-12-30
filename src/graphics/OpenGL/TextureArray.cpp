#include "TextureArray.hpp"

TextureArray::TextureArray (const std::vector<std::string>& paths)
	: m_filePaths (paths), m_data (nullptr), m_width (0), m_height (0), m_bpp (0), m_id (0)
{
	glGenTextures (1, &m_id);
	glBindTexture (GL_TEXTURE_2D_ARRAY, m_id);

	glTexParameteri (GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	stbi_set_flip_vertically_on_load (true);
	m_data = stbi_load (paths.at(0).c_str (), &m_width, &m_height, &m_bpp, 4);
	stbi_image_free (m_data);
	glTexStorage3D (GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, m_width, m_height, paths.size());

	for (int i = 0; i < paths.size (); i++)
	{
		m_data = stbi_load (paths.at (i).c_str (), &m_width, &m_height, &m_bpp, 4);
		if (m_data)
		{
			glTexSubImage3D (GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, m_width, m_height, 1, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
			glGenerateMipmap (GL_TEXTURE_2D_ARRAY);

			stbi_image_free (m_data);
		}
	}
}

TextureArray::~TextureArray ()
{
	glDeleteTextures (1, &m_id);
}

void TextureArray::Bind (unsigned int slot) const
{
	glActiveTexture (GL_TEXTURE0 + slot);
	glBindTexture (GL_TEXTURE_2D_ARRAY, m_id);
}

void TextureArray::Unbind () const
{
	glBindTexture (GL_TEXTURE_2D_ARRAY, 0);
}