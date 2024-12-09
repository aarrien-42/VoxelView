#pragma once

#include <GL/glew.h>

#include "stb_image/stb_image.h"

#include <string>

class Texture {
	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }
	private:
		GLuint m_id;
		std::string m_filePath;
		unsigned char* m_data;
		int m_width, m_height, m_bpp;
};