#pragma once

#include <GL/glew.h>

class Buffer {
	public:
		enum class Type {
			VertexBuffer = GL_ARRAY_BUFFER,
			IndexBuffer = GL_ELEMENT_ARRAY_BUFFER
		};

		Buffer(Type type);
		~Buffer();

		void Bind() const;
		void Unbind() const;

		void SetData(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) const;
	private:
		GLuint m_id;
		Type m_type;
};

class VertexBuffer : public Buffer {
	public:
		VertexBuffer() : Buffer(Buffer::Type::VertexBuffer) {}
};

class IndexBuffer : public Buffer {
	public:
		IndexBuffer() : Buffer(Buffer::Type::IndexBuffer) {}
};