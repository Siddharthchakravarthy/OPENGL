#pragma once
#include <vector>
#include "Renderer.h"
struct VertexBufferElements {
	
	unsigned int count;
	unsigned int type;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};


class VertexBufferLayout {
private:
	std::vector<VertexBufferElements> m_Elements;
	int m_Stride;
public:
	VertexBufferLayout() :m_Stride(0) {}

	template <typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		m_Elements.push_back({count, GL_FLOAT, GL_FALSE });
		m_Stride = m_Stride + count * VertexBufferElements::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
		m_Stride = m_Stride + count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_BYTE);
	}
	template<>
	void Push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		m_Stride = m_Stride + count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_INT);
	}

	inline std::vector<VertexBufferElements> GetElement() const&{
		return m_Elements;
	}
	inline unsigned int GetStride() const {
		return m_Stride;
	}
};