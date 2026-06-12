#include "../vendor/glad/include/glad/glad.h"
#include "IndexBuffer.h"
#include "Object.h"
#include "VertexArray.h"
#include "Window.h"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <array>
#include <iostream>

int main() {

  float centre[3] = {0.0f, 0.0f, 0.0f};
  Quadrilateral *quad_1 = new Quadrilateral(centre, 0.4f, square);

  quad_1->generate_quad();

  std::array<Vertex, 4> vertices = quad_1->get_vertices();
  std::array<int, 6> indices = quad_1->get_indices();

  Window *window = new Window(800, 800, "PHYISCS RENDERER");

  VertexBuffer vertex_buffer(vertices.data(), vertices.size() * sizeof(Vertex));
  IndexBuffer index_buffer(indices.data(), indices.size() * sizeof(int));

  VertexArrayLayout layout;
  layout.add_layout_element({3, GL_FLOAT, GL_FALSE});
  layout.add_layout_element({3, GL_FLOAT, GL_FALSE});

  VertexArrayBuffer *vert_array_buffer = new VertexArrayBuffer(layout);
  vert_array_buffer->add_buffer(vertex_buffer);
  index_buffer.bind();

  Shader *shader = new Shader();
  shader->parse("../src/graphics/solid_color.shader");
  shader->compile_shaders();
  shader->attach_shaders_and_link_program();

  while (!window->should_close()) {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use_shader_program();
    vert_array_buffer->bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    window->swap_buffers();
  }

  delete vert_array_buffer;
  delete shader;

  return 0;
}
