#include "PhysicsWorld.h"
#include "IndexBuffer.h"
#include "Object.h"
#include "PhysicalBody.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <ostream>

PhysicsWorld::PhysicsWorld(unsigned int num_particles, float radius,
                           Renderer *renderer, VertexArrayLayout *layout,
                           Shader *shader, Window *window)
    : m_num_particles(num_particles), m_shader(shader), m_renderer(renderer),
      m_layout(layout), m_window(window), m_particle_radius(radius) {

  std::cout << "CREATED WINDOW" << std::endl;

  int sqrt = (int)std::sqrt(num_particles);
  Circle circle_data(radius, 36);
  circle_data.generate_circle();
  m_particles.reserve(sqrt * sqrt);
  m_vertices = circle_data.get_vertices();
  m_indices = circle_data.get_indices();

  std::cout << "GENERATED DATA" << std::endl;

  m_index_buffer = new IndexBuffer(m_indices.data(), m_indices.size());

  std::cout << "BOUND INDEX BUFFER TO GPU" << std::endl;

  m_vertex_buffer =
      new VertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(Vertex));

  std::cout << "BOUND VERTEX BUFFER TO GPU" << std::endl;

  m_vert_array_buffer = new VertexArrayBuffer(*m_layout);

  std::cout << "CREATED VERTEX ARRAY BUFFER" << std::endl;

  m_vert_array_buffer->add_buffer(*m_vertex_buffer);

  std::cout << "ADDDED BUFFER";

  float radius_offset = 3.0f;

  for (int i = 0; i < sqrt; i++) {
    for (int j = 0; j < sqrt; j++) {

      float x_pos = (2 * i - radius_offset) * (radius + 0.5);
      float y_pos = (2 * j - radius_offset) * (radius + 0.5);

      Particles particle;

      particle.physical_body = new PhysicalBody(
          true, 1.0f, glm::vec3(x_pos, y_pos, 0.0f), 2 * radius, 2 * radius);

      particle.entity = new Entity(m_renderer, particle.physical_body);

      m_particles.push_back(particle);
    }
  }
}

void PhysicsWorld::phyiscs_loop() {
  float delta_time = 0.0f;
  float accumulator = 0.0f;
  float last_frame = 0.0f;

  float FIXED_TIME_STEP = 1.0f / 60.0f;

  m_renderer->init();

  while (!m_window->should_close()) {

    float live_aspect = m_window->get_aspect_ratio();

    float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    accumulator += delta_time;

    while (accumulator >= FIXED_TIME_STEP) {
      for (int i = 0; i < m_num_particles; i++) {

        m_particles[i].entity->Update(FIXED_TIME_STEP);
      }

      accumulator -= FIXED_TIME_STEP;
    }

    int collision_check_iterations = 16;

    for (int i = 0; i < collision_check_iterations; i++) {
      for (int i = 0; i < m_num_particles; i++) {

        m_particles[i].physical_body->check_and_apply_bounding_collision(
            live_aspect);
      }
      check_for_collisions();
    }

    if (glfwGetMouseButton(m_window->get_window(), GLFW_MOUSE_BUTTON_LEFT) ==
        GLFW_PRESS) {
      double xpos, ypos;
      glfwGetCursorPos(m_window->get_window(), &xpos, &ypos);

      int width = m_window->get_current_width();
      int height = m_window->get_current_height();

      float ndc_x = (2.0f * (float)xpos) / (float)width - 1.0f;
      float ndc_y = 1.0f - (2.0f * (float)ypos) / (float)height;

      float world_x = ndc_x * 10.0f * live_aspect;
      float world_y = ndc_y * 10.0f;

      generate_particle(world_x, world_y);
    }

    m_renderer->set_clear_color(0.0f, 1.0f, 0.0f, 1.0f);
    m_renderer->clear();

    for (int i = 0; i < m_particles.size(); i++) {
      m_particles[i].entity->Draw(m_shader, *m_vert_array_buffer,
                                  *m_index_buffer, live_aspect);
    }

    m_window->swap_buffers();
  }
}

void PhysicsWorld::generate_particle(float x, float y) {
  Particles particle;

  particle.physical_body =
      new PhysicalBody(true, 1.0f, glm::vec3(x, y, 0.0f), 2.0f, 2.0f);

  particle.entity = new Entity(m_renderer, particle.physical_body);

  particle.physical_body->set_current_velocity(glm::vec3(1.0f, 1.0f, 0.0f));
  m_particles.push_back(particle);

  m_num_particles++;
}

void PhysicsWorld::check_for_collisions() {
  for (int i = 0; i < m_num_particles - 1; i++) {

    for (int j = i + 1; j < m_num_particles; j++) {

      PhysicalBody *body_1 = m_particles[i].physical_body;
      glm::vec3 body_velo_1 = body_1->get_current_velocity();
      glm::vec3 body_pos_1 = body_1->get_current_position();
      PhysicalBody *body_2 = m_particles[j].physical_body;

      glm::vec3 body_velo_2 = body_2->get_current_velocity();
      glm::vec3 body_pos_2 = body_2->get_current_position();

      float particle_distance = glm::distance(body_pos_2, body_pos_1);
      float target_distance = m_particle_radius * 2;

      if (particle_distance <= target_distance) {

        glm::vec3 collision_normal = glm::normalize(body_pos_2 - body_pos_1);

        float penetration = target_distance - particle_distance;

        glm::vec3 seperation_vector = collision_normal * (penetration / 2.0f);

        body_1->set_current_position(body_pos_1 - seperation_vector);
        body_2->set_current_position(body_pos_2 + seperation_vector);

        glm::vec3 rel_velo = body_velo_1 - body_velo_2;

        float velo_along_normal = glm::dot(rel_velo, collision_normal);

        if (velo_along_normal < 0.0f)
          continue;

        float m1 = body_1->get_mass();
        float m2 = body_2->get_mass();

        float e = 1.0f;

        float impulse_scalar =
            velo_along_normal * (-1.0f - e) / (1.0f / m1 + 1.0f / m2);

        glm::vec3 impulse_vector = collision_normal * impulse_scalar;

        body_1->set_current_velocity(body_velo_1 + (impulse_vector / m1));
        body_2->set_current_velocity(body_velo_2 - (impulse_vector / m2));
      }
    }
  }
}

PhysicsWorld::~PhysicsWorld() {
  for (int i = 0; i < m_num_particles; i++) {
    delete m_particles[i].entity;
    delete m_particles[i].physical_body;
  }
  delete m_shader;
  delete m_renderer;
  delete m_vert_array_buffer;
  delete m_vertex_buffer;
  delete m_index_buffer;
  delete m_window;
}
