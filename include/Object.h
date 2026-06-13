#include "../vendor/glad/include/glad/glad.h"
#include <array>
#include <vector>

enum TriangleTypes { right_angle, equilateral, isoceles };
enum QuadTypes { square, rectangle };

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

class Quadrilateral {
private:
  float m_centre[3];
  float m_width;
  float m_height;
  QuadTypes m_quad_type;
  std::array<Vertex, 4> m_vertices;
  std::array<unsigned int, 6> m_indices;

public:
  Quadrilateral(float centre[3], float width, float height,
                QuadTypes quad_type);
  Quadrilateral(float centre[3], float side, QuadTypes quad_type);

  void generate_quad();

  std::array<Vertex, 4> get_vertices();

  std::array<unsigned int, 6> get_indices();

  ~Quadrilateral();
};

class Circle {
private:
  float m_centre[3];
  float m_radius;
  unsigned int m_res;
  std::vector<Vertex> m_vertices;

public:
  Circle(float centre[3], float radius, unsigned int res);

  void generate_circle();

  std::vector<Vertex> get_vertices();

  ~Circle();
};
