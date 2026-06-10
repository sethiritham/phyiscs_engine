#include "../vendor/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include <vector>

struct VertexArrayLayoutElement {
  unsigned int size;
  unsigned int type;
  unsigned int normalized;
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

public:
  VertexArrayBuffer(VertexArrayLayout layout);

  void bind();

  void add_buffer(const VertexBuffer &vb);

  void unbind();

  ~VertexArrayBuffer();
};
