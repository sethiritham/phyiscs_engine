#include "../vendor/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include <array>
#include <vector>

enum TriangleTypes { right_angle, equilateral, isoceles };

struct Vertex {
  float x;
  float y;
  float z;

  float r;
  float g;
  float b;
};

class Triangle {
private:
  float m_centre[3];
  float m_width;
  float m_height;
  TriangleTypes m_triangle_type;
  std::array<Vertex, 3> m_vertices;

public:
  Triangle(float centre[3], float width, float height,
           TriangleTypes triangle_type);

  std::array<Vertex, 3> generate_vertices();

  ~Triangle();
};
