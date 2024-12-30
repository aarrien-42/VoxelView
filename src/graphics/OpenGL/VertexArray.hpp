#pragma once

#include <GL/glew.h>

#include "Buffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
	public:
		VertexArray ();
		~VertexArray ();

		void Bind () const;
		void Unbind () const;

		void AddVertexBufferLayout (const class VertexBufferLayout& layout);
	private:
		GLuint m_id;
};