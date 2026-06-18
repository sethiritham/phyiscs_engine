#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(void *data, unsigned int count)
    : m_data(data), m_count(count) {
  glGenBuffers(1, &m_Renderer_ID);
}

void IndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), m_data,
               GL_STATIC_DRAW);
}

void IndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

unsigned int IndexBuffer::get_indices_count() const { return m_count; }

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_Renderer_ID); }
