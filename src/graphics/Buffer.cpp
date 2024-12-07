#include "Buffer.hpp"

Buffer::Buffer(Type type) : m_type(type) {
	glGenBuffers(1, &m_id);
}

Buffer::~Buffer() {
	glDeleteBuffers(1, &m_id);
}

void Buffer::Bind() const {
	glBindBuffer(static_cast<GLenum>(m_type), m_id);
}

void Buffer::Unbind() const {
	glBindBuffer(static_cast<GLenum>(m_type), 0);
}

void Buffer::SetData(const void* data, size_t size, GLenum usage) const {
	glBufferData(static_cast<GLenum>(m_type), size, data, usage);
}