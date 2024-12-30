#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "graphics/OpenGL/VertexArray.hpp"
#include "graphics/OpenGL/Buffer.hpp"
#include "graphics/OpenGL/Texture.hpp"
#include "graphics/OpenGL/Shader.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class Mesh {
	public:
		Mesh (std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, Texture &texture);
		~Mesh () = default;

		void SetPosition (const glm::vec3 &position) { m_position = position; }

		glm::vec3 GetPosition () const { return m_position; }
		size_t GetIndexCount () const { return m_indices.size(); }

		void Bind ();
		void Unbind ();
	private:
		void SetupMesh ();

		glm::vec3 m_position;
		std::vector<Vertex> &m_vertices;
		std::vector<unsigned int> &m_indices;
		Texture &m_texture;

		VertexArray m_vao;
		VertexBuffer m_vbo;
		IndexBuffer m_ibo;
};