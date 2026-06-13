#include "../vendor/glm/glm/ext/matrix_float3x3.hpp"
#include "PhysicalBody.h"
#include "Renderer.h"
#include "VertexArray.h"

class Entity {
private:
  Renderer *m_renderer;
  PhysicalBody *m_phyisical_body;

public:
  Entity(Renderer *renderer, PhysicalBody *physical_body);

  void Update(float delta_time);

  void Draw(Shader *shader, const VertexArrayBuffer &vao,
            const IndexBuffer &ibo);

  ~Entity();
};
