#pragma once
#include "../vendor/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "VertexBuffer.h"
#include <vector>

struct VertexArrayLayoutElement {
  unsigned int count;
  unsigned int type;
  unsigned char normalized;
};

class VertexArrayLayout {
private:
  unsigned int m_stride;
  std::vector<VertexArrayLayoutElement> m_vertex_attribs;

public:
  VertexArrayLayout() : m_stride(0) {}

  void add_layout_element(VertexArrayLayoutElement layout_element);

  inline unsigned int get_stride();

  inline std::vector<VertexArrayLayoutElement> get_elemets();

  ~VertexArrayLayout();
};

class VertexArrayBuffer {
private:
  unsigned int m_VertexBuffer_ID;
  VertexArrayLayout layout;

  static unsigned int get_size_of_type(unsigned int type) {
    switch (type) {
    case GL_FLOAT:
      return 4;
    case GL_UNSIGNED_INT:
      return 1;
    case GL_UNSIGNED_BYTE:
      return 1;
    }

    return 0;
  }

public:
  VertexArrayBuffer(VertexArrayLayout layout);

  void bind() const;

  void add_buffer(const VertexBuffer &vb);

  void unbind() const;

  ~VertexArrayBuffer();
};
