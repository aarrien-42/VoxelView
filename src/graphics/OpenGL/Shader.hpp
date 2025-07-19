#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>

class Shader {
	public:
		Shader (const char* vertexPath, const char* fragmentPath);
		~Shader ();

		void Use () const;
		void Unuse () const;

		GLint GetUniformLocation (const std::string& name) const;
		void SetUniform (const std::string& name, int value) const;
		void SetUniform (const std::string& name, float value) const;
		void SetUniform (const std::string& name, float v1, float v2, float v3) const;
		void SetUniform (const std::string& name, const glm::vec3& value) const;
		void SetUniform (const std::string& name, const glm::vec4& value) const;
		void SetUniform (const std::string& name, const glm::mat4& value) const;
	private:
		GLuint m_id;
};