#include "VertexArray.h"

void VertexArrayLayout::add_layout_element(
    VertexArrayLayoutElement layout_element) {
  m_vertex_attribs.push_back(layout_element);
  m_stride += sizeof(layout_element);
}

unsigned int VertexArrayLayout::get_stride() { return m_stride; }

std::vector<VertexArrayLayoutElement> VertexArrayLayout::get_elemets() {
  return m_vertex_attribs;
}

VertexArrayLayout::~VertexArrayLayout() {}

VertexArrayBuffer::VertexArrayBuffer(VertexArrayLayout layout)
    : layout(layout) {
  glGenVertexArrays(1, &m_VertexBuffer_ID);
}

void VertexArrayBuffer::add_buffer(const VertexBuffer &vb) {
  bind();
  vb.bind();
  std::vector<VertexArrayLayoutElement> elements;
  elements = layout.get_elemets();

  unsigned int stride = layout.get_stride();

  for (unsigned int i = 0; i < elements.size(); i++) {
    glVertexAttribPointer(i, elements[i].size, elements[i].type,
                          elements[i].normalized, stride,
                          (void *)(i * elements[i].size));

    glEnableVertexAttribArray(i);
  }
}

void VertexArrayBuffer::bind() { glBindVertexArray(m_VertexBuffer_ID); }

void VertexArrayBuffer::unbind() { glBindVertexArray(0); }

VertexArrayBuffer::~VertexArrayBuffer() {
  glDeleteVertexArrays(1, &m_VertexBuffer_ID);
}
