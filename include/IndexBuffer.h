#include "../vendor/glad/include/glad/glad.h"

class IndexBuffer {
private:
  unsigned int m_Renderer_ID;
  void *m_data;
  unsigned int m_size;

public:
  IndexBuffer(void *data, unsigned int size);

  void bind();

  void unbind();

  ~IndexBuffer();
};
