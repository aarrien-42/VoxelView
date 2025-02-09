#include "Font.hpp"

#include <iostream>
#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_TRUETYPE_IMPLEMENTATION 
#include "stb_truetype.h"

Font::Font (const std::string& fontPath, int fontSize)
{
    LoadFont (fontPath);
    if (!fontBuffer.empty ())
    {
        GenerateTextureAtlas (fontSize);
    }
}

Font::~Font ()
{
    glDeleteTextures (1, &textureID);
}

// Load font file into memory
void Font::LoadFont (const std::string& fontPath)
{
    FILE* fontFile = fopen (fontPath.c_str (), "rb");
    if (!fontFile)
    {
        std::cerr << "Failed to open font file: " << fontPath << std::endl;
        return;
    }

    fseek (fontFile, 0, SEEK_END);
    long size = ftell (fontFile);
    fseek (fontFile, 0, SEEK_SET);
    fontBuffer.resize (size);
    fread (fontBuffer.data (), size, 1, fontFile);
    fclose (fontFile);

    if (!stbtt_InitFont (&fontInfo, fontBuffer.data (), 0))
    {
        std::cerr << "Failed to initialize font." << std::endl;
        fontBuffer.clear ();
    }
}

void Font::GenerateTextureAtlas (int fontSize)
{
    float scale = stbtt_ScaleForPixelHeight (&fontInfo, fontSize);
    int atlasWidth = 512, atlasHeight = 256;
    std::vector<unsigned char> bitmap (atlasWidth * atlasHeight, 0);

    int xOffset = 0, yOffset = 0, maxRowHeight = 0;
    for (char c = 32; c < 127; ++c)
    {
        int w, h, xOff, yOff;
        unsigned char* glyphBitmap = stbtt_GetCodepointBitmap (&fontInfo, 0, scale, c, &w, &h, &xOff, &yOff);

        if (xOffset + w >= atlasWidth)
        {
            xOffset = 0;
            yOffset += maxRowHeight;
            maxRowHeight = 0;
        }

        for (int row = 0; row < h; ++row)
        {
            for (int col = 0; col < w; ++col)
            {
                bitmap[(yOffset + row) * atlasWidth + (xOffset + col)] = glyphBitmap[row * w + col];
            }
        }

        int advance, lsb;
        stbtt_GetCodepointHMetrics (&fontInfo, c, &advance, &lsb);

        characters[c] = { (float)xOffset / atlasWidth, (float)yOffset / atlasHeight,
                          (float)(xOffset + w) / atlasWidth, (float)(yOffset + h) / atlasHeight,
                          w, h, xOff, yOff, advance * (int)scale };

        xOffset += w + 2;
        maxRowHeight = std::max (maxRowHeight, h);
        stbtt_FreeBitmap (glyphBitmap, nullptr);
    }

    // Save the texture atlas to a file
    stbi_write_png ("TextAtlas.png", atlasWidth, atlasHeight, 1, bitmap.data (), atlasWidth);

    glGenTextures (1, &textureID);
    glBindTexture (GL_TEXTURE_2D, textureID);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RED, atlasWidth, atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.data ());
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
