#pragma once

#include <GL/glew.h>

#include <stb/stb_truetype.h>

#include <string>
#include <unordered_map>
#include <vector>

// Structure to hold character metadata for rendering
struct Character {
    float u0, v0, u1, v1; // Texture coordinates
    int width, height;    // Glyph size
    int bearingX, bearingY; // Offset from baseline
    int advance;          // Advance to the next character
};

class Font {
    public:
        Font (const std::string& fontPath, int fontSize);
        ~Font ();

        GLuint GetTextureID () const { return textureID; }
        const Character& GetCharacter (char c) const { return characters.at (c); }

    private:
        void LoadFont (const std::string& fontPath);
        void GenerateTextureAtlas (int fontSize);

        GLuint textureID;
        stbtt_fontinfo fontInfo;
        std::unordered_map<char, Character> characters;
        std::vector<unsigned char> fontBuffer;
};

