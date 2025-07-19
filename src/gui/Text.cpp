#include "Text.hpp"

Text::Text (const std::string& text, Font& font)
	: m_text (text), m_font (font), m_position (0.0f, 0.0f)
{
}

