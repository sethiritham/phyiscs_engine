#include "VertexArray.h"
#include <cstdint>

void VertexArrayLayout::add_layout_element(
    VertexArrayLayoutElement layout_element) {
  m_vertex_attribs.push_back(layout_element);
  m_stride += 3 * sizeof(unsigned int);
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
  int accumalator = 0;
  size_t offset = 0;

  for (unsigned int i = 0; i < elements.size(); i++) {

    glVertexAttribPointer(i, elements[i].count, elements[i].type,
                          elements[i].normalized, stride,
                          (void *)(intptr_t)offset);

    glEnableVertexAttribArray(i);

    accumalator += elements[i].count;
    offset += elements[i].count * get_size_of_type(elements[i].type);
  }
}

void VertexArrayBuffer::bind() { glBindVertexArray(m_VertexBuffer_ID); }

void VertexArrayBuffer::unbind() { glBindVertexArray(0); }

VertexArrayBuffer::~VertexArrayBuffer() {
  glDeleteVertexArrays(1, &m_VertexBuffer_ID);
}
