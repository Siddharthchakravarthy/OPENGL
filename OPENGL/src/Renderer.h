#pragma once
#include<GL/glew.h>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(y) GLClearError();y;ASSERT(GLLogCall(#y, __FILE__, __LINE__))

void GLClearError(); 
// since assert is a boolean we need to change the GLLogCall's type to boolean
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {

public:
	const void Clear();
	void Draw(IndexBuffer &ib, VertexArray& va, Shader &shader) const;
};

