#include "VertexArray.hpp"

VertexArray::VertexArray ()
{
	glGenVertexArrays (1, &m_id);
}

VertexArray::~VertexArray ()
{
	glDeleteVertexArrays (1, &m_id);
}

void VertexArray::Bind () const
{
	glBindVertexArray (m_id);
}

void VertexArray::Unbind () const
{
	glBindVertexArray (0);
}

void VertexArray::AddVertexBufferLayout (const VertexBufferLayout& layout)
{
	const auto& elements = layout.GetElements ();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size (); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray (i);
		glVertexAttribPointer (i, element.count, element.type, element.normalized, layout.GetStride (), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType (element.type);
	}
}