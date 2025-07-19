#pragma once

#include <glm/glm.hpp>
#include "gui/Font.hpp"

class Text {
	public:
		Text (const std::string& text, Font& font);
		~Text () = default;

		void SetPosition (const glm::vec2& position) { m_position = position; }
		void SetColor (const glm::vec3& color) { m_color = color; }

		std::string GetText () const { return m_text; }
		glm::vec2 GetPosition () const { return m_position; }
		glm::vec3 GetColor () const { return m_color; }
		Font& GetFont () const { return m_font; }

	private:
		std::string m_text;
		glm::vec2 m_position;
		glm::vec3 m_color;
		Font& m_font;
};
