#pragma once
#include "../vendor/glad/include/glad/glad.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "shader.h"
#include <glm/ext/matrix_float3x3.hpp>

class Renderer {
public:
  void init() const;

  void set_wireframe_mode(bool enabled) const;

  void clear() const;
  void set_clear_color(float r, float g, float b, float a) const;

  void draw(const VertexArrayBuffer &vao, const IndexBuffer &ibo,
            const Shader &shader) const;
};
