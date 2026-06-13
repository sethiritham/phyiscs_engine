#include "Renderer.h"
#include <cstddef>

void Renderer::init() const {
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::clear() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::set_wireframe_mode(bool enabled) const {
  if (enabled) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void Renderer::set_clear_color(float r, float g, float b, float a) const {
  glClearColor(r, g, b, a);
}

void Renderer::draw(const VertexArrayBuffer &vao, const IndexBuffer &ibo,
                    const Shader &shader) const {
  shader.use_shader_program();
  vao.bind();
  ibo.bind();

  glDrawElements(GL_TRIANGLES, ibo.get_indices_count(), GL_UNSIGNED_INT, NULL);

  vao.unbind();
  ibo.unbind();
}
