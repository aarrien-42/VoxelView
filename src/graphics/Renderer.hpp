#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

#include "graphics/Mesh.hpp"
#include "graphics/OpenGL/Shader.hpp"
#include "scene/Camera.hpp"

class Renderer {
	public:
		Renderer();
		~Renderer() = default;

		void SetCamera(Camera &camera) { m_camera = &camera; }

		bool Init();
		void Clear();
		void Draw(GLsizei count, GLenum mode = GL_TRIANGLES);
		void Draw(Mesh& mesh, Shader& shader);

		void SetClearColor(const glm::vec4& color);
	private:
		Camera *m_camera;
};