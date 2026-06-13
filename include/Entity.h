#include "../vendor/glm/glm/ext/matrix_float3x3.hpp"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexArray.h"
#include <type_traits>

struct VirtualMesh {
  unsigned int VBO;
  unsigned int VAO;
  unsigned int IBO;
};
