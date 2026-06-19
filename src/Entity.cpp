#include "Entity.h"
#include "Renderer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "shader.h"

Entity::Entity(Renderer *renderer, PhysicalBody *physical_body)
    : m_renderer(renderer), m_phyisical_body(physical_body) {}

void Entity::Update(float delta_time) { m_phyisical_body->Step(delta_time); }

void Entity::Draw(Shader *shader, const VertexArrayBuffer &vao,
                  const IndexBuffer &ibo, float aspect_ratio) {
  glm::vec3 pos = m_phyisical_body->get_current_position();
  glm::mat4 model(1.0f);

  model = glm::translate(model, pos);

  glm::mat4 projection =
      glm::ortho(-10.0f * aspect_ratio, 10.0f * aspect_ratio, -10.0f, 10.0f);

  shader->use_shader_program();
  shader->set_uniform_mat4("u_model_matrix", model);
  shader->set_uniform_mat4("u_projection_matrix", projection);
  shader->set_uniform_float("u_aspect_ratio", aspect_ratio);

  m_renderer->draw(vao, ibo, *shader);
}

Entity::~Entity() {}
