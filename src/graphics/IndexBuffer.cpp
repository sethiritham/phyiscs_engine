#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(void *data, unsigned int size)
    : m_data(data), m_size(size) {
  glGenBuffers(1, &m_Renderer_ID);
}

void IndexBuffer::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, m_data, GL_STATIC_DRAW);
}

void IndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_Renderer_ID); }
