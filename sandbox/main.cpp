#include "../vendor/glad/include/glad/glad.h"
#include "Object.h"
#include "VertexArray.h"
#include "Window.h"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <array>
#include <iostream>

int main() {

  float centre[3] = {0.0f, 0.0f, 0.0f};
  Triangle *triangle_1 = new Triangle(centre, 0.2f, 0.2f, right_angle);
  std::array<Vertex, 3> vertices = triangle_1->generate_vertices();

  Window *window = new Window(800, 800, "PHYISCS RENDERER");

  VertexBuffer vertex_buffer(vertices.data(), vertices.size() * sizeof(Vertex));

  VertexArrayLayout layout;
  layout.add_layout_element({3, GL_FLOAT, GL_FALSE});
  layout.add_layout_element({3, GL_FLOAT, GL_FALSE});

  VertexArrayBuffer *vert_array_buffer = new VertexArrayBuffer(layout);
  vert_array_buffer->add_buffer(vertex_buffer);

  Shader *shader = new Shader();
  shader->parse("../src/graphics/solid_color.shader");
  shader->compile_shaders();
  shader->attach_shaders_and_link_program();

  while (!window->should_close()) {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use_shader_program();
    vert_array_buffer->bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    window->swap_buffers();
  }

  delete vert_array_buffer;
  delete shader;

  return 0;
}
