#pragma once
#include "Entity.h"
#include "IndexBuffer.h"
#include "Object.h"
#include "PhysicalBody.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <vector>

struct Particles {
  PhysicalBody *physical_body;
  Entity *entity;
};

class PhysicsWorld {
private:
  float m_particle_radius;
  Window *m_window;
  unsigned int m_num_particles;
  std::vector<Particles> m_particles;
  std::vector<Vertex> m_vertices;
  VertexBuffer *m_vertex_buffer;
  IndexBuffer *m_index_buffer;
  VertexArrayBuffer *m_vert_array_buffer;
  std::vector<unsigned int> m_indices;
  Renderer *m_renderer;
  VertexArrayLayout *m_layout;
  Shader *m_shader;

public:
  PhysicsWorld(unsigned int num_particles, float radius, Renderer *renderer,
               VertexArrayLayout *layout, Shader *shader, Window *window);

  void check_for_collisions();

  void phyiscs_loop();

  void generate_particle();

  ~PhysicsWorld();
};
