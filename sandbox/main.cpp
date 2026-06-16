#include "../vendor/glad/include/glad/glad.h"
#include "Entity.h"
#include "IndexBuffer.h"
#include "Object.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Window.h"
#include "glm/ext/vector_float3.hpp"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <vector>

int main() {

  float centre[3] = {0.0f, 0.0f, 0.0f};
  Circle circ_1(centre, 1.0f, 36);

  circ_1.generate_circle();

  std::vector<Vertex> vertices = circ_1.get_vertices();
  std::vector<unsigned int> indices = circ_1.get_indices();

  Window *window = new Window(800, 800, "PHYISCS RENDERER");

  VertexBuffer vertex_buffer(vertices.data(), vertices.size() * sizeof(Vertex));
  IndexBuffer index_buffer(indices.data(), indices.size());

  VertexArrayLayout layout;
  layout.add_layout_element({3, GL_FLOAT, GL_FALSE});
  layout.add_layout_element({3, GL_FLOAT, GL_FALSE});

  VertexArrayBuffer vert_array_buffer(layout);
  vert_array_buffer.add_buffer(vertex_buffer);
  index_buffer.bind();

  Shader shader;
  shader.parse("../src/graphics/solid_color.shader");
  shader.compile_shaders();
  shader.attach_shaders_and_link_program();

  Renderer renderer;

  float delta_time = 0.0f;
  float accumulator = 0.0f;
  float last_frame = 0.0f;

  PhysicalBody physical_body(
      true, 3.0f, glm::vec3(centre[0], centre[1], centre[2]), 2.0f, 2.0f);

  Entity entity(&renderer, &physical_body);

  float FIXED_TIME_STEP = 1.0f / 60.0f;
  renderer.init();

  while (!window->should_close()) {

    float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    accumulator += delta_time;

    while (accumulator >= FIXED_TIME_STEP) {
      entity.Update(FIXED_TIME_STEP);

      accumulator -= FIXED_TIME_STEP;
    }

    renderer.set_clear_color(0.0f, 1.0f, 0.0f, 1.0f);
    renderer.clear();

    entity.Draw(&shader, vert_array_buffer, index_buffer,
                window->get_aspect_ratio());

    window->swap_buffers();
  }

  delete window;
  return 0;
}
