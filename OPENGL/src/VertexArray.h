#pragma once
#include "VertexBuffer.h"


class VertexBufferLayout;


class VertexArray
{
private:
	unsigned int m_RendererID_of_va;
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void UnBind();
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

