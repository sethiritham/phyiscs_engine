#pragma once
#include "../vendor/glad/include/glad/glad.h"

class IndexBuffer {
private:
  unsigned int m_Renderer_ID;
  void *m_data;
  unsigned int m_count;

public:
  IndexBuffer(void *data, unsigned int count);

  void bind() const;

  unsigned int get_indices_count() const;

  void unbind() const;

  ~IndexBuffer();
};
