#include "../vendor/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>

struct VertexArrayLayoutElement {
  unsigned int size;
  unsigned int type;
  unsigned int normalized;
};

class VertexArrayBuffer {
private:
  unsigned int m_VertexBuffer_ID;
  std::vector<VertexArrayLayoutElement> m_vertex_attribs;

public:
  VertexArrayBuffer();

  void add_layout(VertexArrayLayoutElement layout) {
    m_vertex_attribs.push_back(layout);
  }

  void bind();

  ~VertexArrayBuffer();
};
