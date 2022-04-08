#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include <iostream>
void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}
// since assert is a boolean we need to change the GLLogCall's type to boolean
bool GLLogCall(const char* function, const char* file, int line) {

    while (unsigned int error = glGetError()) {

        std::cout << error << " " << function << " " << file << " " << line << std::endl;
        return false;
    }
    return true;
}

const void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(IndexBuffer &ib, VertexArray &va, Shader &shader) const
{
    ib.Bind();
    va.Bind();
    shader.Bind();
    
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
