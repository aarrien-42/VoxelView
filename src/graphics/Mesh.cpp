#include "Mesh.hpp"

Mesh::Mesh (std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
	: m_position (0.0f, 0.0f, 0.0f), m_vertices (vertices), m_indices (indices)
{
	SetupMesh ();
}

void Mesh::Bind ()
{
	m_vao.Bind ();
}

void Mesh::Unbind ()
{
	m_vao.Unbind ();
}

void Mesh::SetupMesh ()
{
	// Vertex Array
	m_vao.Bind ();

	// Vertex Buffer
	m_vbo.Bind ();
	m_vbo.SetData (&m_vertices[0], m_vertices.size () * sizeof (Vertex));

	// Index Buffer
	m_ibo.Bind ();
	m_ibo.SetData (&m_indices[0], m_indices.size () * sizeof (unsigned int));

	// Vertex Buffer Layout
	VertexBufferLayout layout;
	layout.Push<float> (3);        // position
	layout.Push<float> (3);        // normal
	layout.Push<float> (2);        // texture
	layout.Push<unsigned int> (1); // texture index
	m_vao.AddVertexBufferLayout (layout);

	// Unbind
	m_vao.Unbind ();
}