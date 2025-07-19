#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <map>

// Structure to hold character metadata for rendering
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Font {
    public:
        Font (const std::string& fontPath, int fontSize);
        ~Font ();

        inline Character GetChar (char c) const { return m_characters.at(c); }
    private:
        bool Init (const std::string& fontPath);

        unsigned int m_fontWidth, m_fontHeight;
        std::map<char, Character> m_characters;
};
