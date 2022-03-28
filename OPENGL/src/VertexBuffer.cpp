#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void *data, int size) {
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    /*&buffer or */
    // illi tanaka bari generate a buffer with a specific number of address, assign a buffer in this case with
    // the buffer variable itself, we are assigning this one like an ID, and then finally give the buffer the 
    // data that bunch of data i mentioned in the book adna mention maadi idbeku that is the size of the buffer
}
VertexBuffer::~VertexBuffer()  {
	GLCall( glDeleteBuffers(1, &m_RendererID) )
}
void VertexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}
void VertexBuffer:: Unbind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}