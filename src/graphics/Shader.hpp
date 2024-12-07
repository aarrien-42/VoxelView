#pragma once

#include <GL/glew.h>

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>

class Shader {
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		GLuint m_id;
};