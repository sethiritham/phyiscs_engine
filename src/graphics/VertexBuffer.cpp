#include "VertexBuffer.h"
#include "Object.h"

VertexBuffer::VertexBuffer(void *data, int size) : m_data(data), m_size(size) {
  glGenBuffers(1, &m_renderer_ID);
}

void VertexBuffer::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID);
  glBufferData(GL_ARRAY_BUFFER, m_size, m_data, GL_STATIC_DRAW);
}

void VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_renderer_ID); }

unsigned int VertexBuffer::get_vertices_count() {
  unsigned int count = m_size / sizeof(Vertex);
}
