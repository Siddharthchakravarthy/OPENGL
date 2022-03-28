#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count){
	GLCall(glGenBuffers(1, &m_RendererID_of_ind_buff));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID_of_ind_buff));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    /*&buffer or */
    // illi tanaka bari generate a buffer with a specific number of address, assign a buffer in this case with
    // the buffer variable itself, we are assigning this one like an ID, and then finally give the buffer the 
    // data that bunch of data i mentioned in the book adna mention maadi idbeku that is the size of the buffer
}
IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID_of_ind_buff));
}
void IndexBuffer::Bind() const{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID_of_ind_buff));
}
void IndexBuffer:: Unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
unsigned int IndexBuffer::GetCount() {
	return m_count;
}