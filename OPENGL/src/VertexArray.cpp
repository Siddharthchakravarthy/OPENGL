#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
VertexArray::VertexArray() 
{
    glGenVertexArrays(1, &m_RendererID_of_va); // GL_ARRAY_BUFFER anta enu ond array ge bind maadood bekilla buffer stage nalli
                                                  //nalli maadboodu
}

VertexArray::~VertexArray()
{
}

void VertexArray::Bind()
{
    glBindVertexArray(m_RendererID_of_va);
}
void VertexArray::UnBind() {
    glBindVertexArray(0);
}
void VertexArray::AddBuffer(const VertexBuffer& vb,const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const std::vector<VertexBufferElements>& elements = layout.GetElement();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        // amele idna naavu draw maadakke layout set maadbeku amele ee layout na naavu shader mukaantara draw maadtivi.
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, elements[i].count, elements[i].type,
            elements[i].normalized, layout.GetStride(),(const void*) offset); // this code links the vertex array object 
        //and the vertex buffer
        offset = offset + elements[i].count * VertexBufferElements::GetSizeOfType(elements[i].type);
    }
}
