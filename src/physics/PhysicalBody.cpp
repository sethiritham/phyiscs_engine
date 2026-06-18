#include "PhysicalBody.h"
#include "glm/ext/vector_float3.hpp"

PhysicalBody::PhysicalBody(bool apply_gravity, float mass,
                           glm::vec3 initial_position, float width,
                           float height)
    : m_mass(mass), m_apply_gravity(apply_gravity),
      m_current_position(initial_position), m_width(width), m_height(height) {
  m_current_velocity = glm::vec3(0.0f);
  m_gravity = glm::vec3(0.0f, -9.81f, 0.0f);
  m_res = 0.8f;
}

glm::vec3 PhysicalBody::get_current_position() { return m_current_position; }

glm::vec3 PhysicalBody::get_current_velocity() { return m_current_velocity; }

void PhysicalBody::Step(float delta_time) {
  if (m_apply_gravity) {
    m_current_velocity = m_current_velocity + m_gravity * delta_time;
    m_current_position += m_current_velocity * delta_time;
  }

  check_and_apply_bounding_collision();
}

void PhysicalBody::check_and_apply_bounding_collision() {
  if (m_current_position.y <= -1.0f * (10.0f - m_height / 2.0f)) {

    m_current_position.y = -1.0f * (10.0f - m_height / 2.0f);
    m_current_velocity.y = -1.0f * m_current_velocity.y * m_res;
  }
}

void PhysicalBody::set_current_velocity(glm::vec3 velo) {
  m_current_velocity = velo;
}

void PhysicalBody::set_current_position(glm::vec3 pos) {
  m_current_position = pos;
}
void PhysicalBody::set_restituion(float res) { m_res = res; }
