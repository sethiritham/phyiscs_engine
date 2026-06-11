#include "../vendor/glad/include/glad/glad.h"

class VertexBuffer {
private:
  unsigned int m_renderer_ID;
  void *m_data;
  unsigned int m_size;

public:
  VertexBuffer(void *data, int size);

  void bind() const;

  void unbind() const;

  ~VertexBuffer();
};
