#include "Font.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <fstream>

Font::Font (const std::string& fontPath, int fontSize)
	: m_fontWidth (0), m_fontHeight (fontSize)
{
    Init (fontPath);
}

Font::~Font ()
{
	for (auto& character : m_characters) {
		glDeleteTextures (1, &character.second.TextureID);
	}
}

bool Font::Init (const std::string& fontPath)
{
    FT_Library ft;
    if (FT_Init_FreeType (&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }

    FT_Face face;
    if (FT_New_Face (ft, fontPath.c_str (), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }
    else
    {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes (face, m_fontWidth, m_fontHeight);

        // disable byte-alignment restriction
        glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char (face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }

            // generate texture
            unsigned int texture;
            glGenTextures (1, &texture);
            glBindTexture (GL_TEXTURE_2D, texture);
            
            // set texture options
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            
            // load data into texture
            glTexImage2D (
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            // now store character for later use
            Character character = {
                texture,
                glm::ivec2 (face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2 (face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            m_characters.insert (std::pair<char, Character> (c, character));
        }
        glBindTexture (GL_TEXTURE_2D, 0);
    }

    // destroy FreeType once we're finished
    FT_Done_Face (face);
    FT_Done_FreeType (ft);

    return true;
}