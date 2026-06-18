#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class PhysicalBody {
private:
  bool m_apply_gravity;
  float m_mass;
  glm::vec3 m_current_position;
  glm::vec3 m_current_velocity;
  glm::vec3 m_gravity;
  float m_width;
  float m_height;
  float m_res;

public:
  PhysicalBody(bool apply_gravity, float mass, glm::vec3 initial_position,
               float width, float height);

  void Step(float delta_time);

  void check_and_apply_bounding_collision();

  glm::vec3 get_current_position();

  glm::vec3 get_current_velocity();

  void set_current_velocity(glm::vec3 velo);

  void set_current_position(glm::vec3 pos);

  void set_restituion(float res);
};
