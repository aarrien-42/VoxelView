#pragma once

#include <GL/glew.h>

#include "stb/stb_image.h"

#include <string>
#include <vector>
#include <iostream>

class TextureArray {
	public:
		TextureArray (const std::vector<std::string>& paths);
		~TextureArray ();

		void Bind (unsigned int slot = 0) const;
		void Unbind () const;

		inline int GetWidth () const { return m_width; }
		inline int GetHeight () const { return m_height; }
	private:
		GLuint m_id;

		std::vector<std::string> m_filePaths;
		int m_width, m_height, m_bpp;
		unsigned char* m_data;
};