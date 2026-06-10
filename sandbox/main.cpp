#include "../vendor/glad/include/glad/glad.h"
#include "VertexArray.h"
#include "Window.h"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <iostream>

void frame_buffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {

  float vertices[9] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

  Window window(800, 800, "PHYISCS RENDERER");

  VertexBuffer vertex_buffer(vertices, sizeof(vertices));

  VertexArrayLayout layout;

  layout.add_layout_element({3, GL_FLOAT, GL_FALSE});

  VertexArrayBuffer *vert_array_buffer = new VertexArrayBuffer(layout);

  vert_array_buffer->add_buffer(vertex_buffer);

  shaderSources shader_sources =
      parseShader("../src/graphics/solid_color.shader");

  const char *vertex_shader_source = shader_sources.vertexShaderSource.c_str();
  const char *fragment_shader_source =
      shader_sources.fragmentShaderSource.c_str();

  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  while (!window.should_close()) {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    vert_array_buffer->bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.swap_buffers();
  }

  delete vert_array_buffer;

  glDeleteProgram(shader_program);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return 0;
}
