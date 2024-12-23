#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, Texture &texture)
	: m_vertices(vertices), m_indices(indices), m_texture(texture)
{
	SetupMesh();
}

void Mesh::Bind() {
	m_texture.Bind();
	m_vao.Bind();
}

void Mesh::Unbind() {
	m_texture.Unbind();
	m_vao.Unbind();
}

void Mesh::SetupMesh()
{
	// Vertex Array
	m_vao.Bind();

	// Vertex Buffer
	m_vbo.Bind();
	m_vbo.SetData(&m_vertices[0], m_vertices.size() * sizeof(Vertex));

	// Index Buffer
	m_ibo.Bind();
	m_ibo.SetData(&m_indices[0], m_indices.size() * sizeof(unsigned int));

	// Vertex Buffer Layout
	VertexBufferLayout layout;
	layout.Push<float>(3); // position
	layout.Push<float>(3); // normal
	layout.Push<float>(2); // texture
	m_vao.AddVertexBufferLayout(layout);
	
	// Unbind
	m_vao.Unbind();
}