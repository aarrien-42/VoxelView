#pragma once

#include <GL/glew.h>
#include <vector>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type) {
			case GL_FLOAT:			return sizeof(float);
			case GL_UNSIGNED_INT:	return sizeof(unsigned int);
		}
		throw std::runtime_error("Unsupported type in VertexBufferLayout");
		return 0;
	}
};

class VertexBufferLayout {
	public:
		VertexBufferLayout()
			: m_stride(0) {}

		template<typename T>
		void Push(unsigned int count) {
			unsigned int type = GetGLType<T>();
			unsigned char normalized = IsNormalized<T>();

			if (type != GL_FLOAT || type != GL_UNSIGNED_INT) {
				throw std::runtime_error("Unsupported type in VertexBufferLayout");
			}

			m_elements.push_back({ type, count, normalized });
			m_stride += count * VertexBufferElement::getSizeOfType(type);
		}

		inline const std::vector<VertexBufferElement> GetElements() const { return m_elements; }
		inline unsigned int GetStride() const { return m_stride; }
	private:
		std::vector<VertexBufferElement> m_elements;
		unsigned int m_stride;

		// Helper for OpenGL type mapping
		template<typename T>
		static unsigned int GetGLType() {
			if constexpr (std::is_same<T, float>::value) {
				return GL_FLOAT;
			} else if constexpr (std::is_same<T, unsigned int>::value) {
				return GL_UNSIGNED_INT;
			} else if constexpr (std::is_same<T, unsigned char>::value) {
				return GL_UNSIGNED_BYTE;
			} else {
				throw std::runtime_error("Unsupported type in VertexBufferLayout");
			}
		}

		// Helper for normalization mapping
		template<typename T>
		static bool IsNormalized() {
			return std::is_same<T, unsigned char>::value;
		}
};
