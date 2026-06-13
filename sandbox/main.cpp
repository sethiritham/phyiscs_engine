#include "../vendor/glad/include/glad/glad.h"
#include "IndexBuffer.h"
#include "Object.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Window.h"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <array>
#include <iostream>
#include <vector>

int main() {

  float centre[3] = {0.0f, 0.0f, 0.0f};
  Quadrilateral *quad_1 = new Quadrilateral(centre, 0.4f, 0.7f, square);
  Circle *circ_1 = new Circle(centre, 0.2f, 36);

  quad_1->generate_quad();
  circ_1->generate_circle();

  // std::vector<Vertex> vertices = circ_1->get_vertices();

  std::array<Vertex, 4> vertices = quad_1->get_vertices();
  std::array<unsigned int, 6> indices = quad_1->get_indices();

  Window *window = new Window(800, 800, "PHYISCS RENDERER");

  VertexBuffer vertex_buffer(vertices.data(), vertices.size() * sizeof(Vertex));
  IndexBuffer index_buffer(indices.data(), indices.size());

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

  Renderer *renderer = new Renderer();

  while (!window->should_close()) {
    renderer->set_clear_color(0.0f, 1.0f, 0.0f, 1.0f);
    renderer->clear();

    renderer->init();
    renderer->draw(*vert_array_buffer, index_buffer, *shader);
    window->swap_buffers();
  }

  delete circ_1;
  delete quad_1;
  delete vert_array_buffer;
  delete shader;
  delete renderer;

  delete window;
  return 0;
}
