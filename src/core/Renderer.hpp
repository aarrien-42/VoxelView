#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

class Renderer {
	public:
		Renderer();
		~Renderer();

		bool Init();
		void Clear();
		void Draw(GLenum mode = GL_TRIANGLES);

		void SetClearColor(const glm::vec4& color);
	private:
};