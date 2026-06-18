#include "../vendor/glad/include/glad/glad.h"
#include "PhysicsWorld.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "shader.h"
#include <GLFW/glfw3.h>

int main() {

  Window *window = new Window(800, 800, "PHYSICS RENDERER");

  VertexArrayLayout *layout = new VertexArrayLayout();
  layout->add_layout_element({3, GL_FLOAT, GL_FALSE});
  layout->add_layout_element({3, GL_FLOAT, GL_FALSE});

  Shader *shader = new Shader();
  shader->parse("../src/graphics/solid_color.shader");
  shader->compile_shaders();
  shader->attach_shaders_and_link_program();

  Renderer *renderer = new Renderer;
  PhysicsWorld world(16, 1.0f, renderer, layout, shader, window);

  world.phyiscs_loop();

  return 0;
}
