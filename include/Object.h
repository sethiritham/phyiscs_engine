#pragma once
#include "../vendor/glad/include/glad/glad.h"
#include "PhysicalBody.h"
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

class Object {
protected:
  float m_current_position[3];

public:
  Object(float starting_position[3]);
};

class Triangle : public Object {
private:
  float m_width;
  float m_height;
  TriangleTypes m_triangle_type;
  std::array<Vertex, 3> m_vertices;

public:
  Triangle(float starting_position[3], float width, float height,
           TriangleTypes triangle_type);

  std::array<Vertex, 3> generate_vertices();

  ~Triangle();
};

class Quadrilateral : Object {
private:
  float m_width;
  float m_height;
  std::array<Vertex, 4> m_vertices;
  std::array<unsigned int, 6> m_indices;

public:
  Quadrilateral(float starting_position[3], float width, float height);
  Quadrilateral(float starting_position[3], float side);

  void generate_quad();

  std::array<Vertex, 4> get_vertices();

  std::array<unsigned int, 6> get_indices();

  ~Quadrilateral();
};

class Circle : Object {
private:
  float m_radius;
  unsigned int m_res;
  std::vector<Vertex> m_vertices;
  std::vector<unsigned int> m_indices;

public:
  Circle(float starting_position[3], float radius, unsigned int res);

  void generate_circle();

  std::vector<Vertex> get_vertices();

  std::vector<unsigned int> get_indices();

  ~Circle();
};
