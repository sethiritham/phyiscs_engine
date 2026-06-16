#include "Object.h"
#include <vector>
#define PI 3.14159265358979323846
#include <cmath>

Object::Object(float starting_position[3])
    : m_current_position{starting_position[0], starting_position[1],
                         starting_position[2]} {}

Triangle::Triangle(float starting_position[3], float width, float height,
                   TriangleTypes triangle_type)
    : Object(starting_position), m_width(width), m_height(height) {}

std::array<Vertex, 3> Triangle::generate_vertices() {
  switch (m_triangle_type) {
  case right_angle:
    m_vertices[0] = {m_current_position[0],
                     m_current_position[1],
                     m_current_position[2],
                     1.0f,
                     0.0f,
                     0.0f};
    m_vertices[1] = {m_current_position[0] + m_width,
                     m_current_position[1],
                     m_current_position[2],
                     1.0f,
                     0.0f,
                     0.0f};
    m_vertices[2] = {m_current_position[0],
                     m_current_position[1] + m_height,
                     m_current_position[2],
                     1.0f,
                     0.0f,
                     0.0f};
    break;
  case equilateral:
    break;
  case isoceles:
    break;
  default:
    break;
  }

  return m_vertices;
}

Quadrilateral::Quadrilateral(float starting_position[3], float width,
                             float height)
    : Object(starting_position), m_height(height), m_width(width) {}

Quadrilateral::Quadrilateral(float starting_position[3], float side)
    : Object(starting_position), m_height(side), m_width(side) {}

void Quadrilateral::generate_quad() {
  Vertex pt_1;
  Vertex pt_2;
  Vertex pt_3;
  Vertex pt_4;

  pt_1 = {m_current_position[0] - m_width / 2.0f,
          m_current_position[1] - m_height / 2.0f,
          m_current_position[2],
          1.0f,
          0.0f,
          0.0f};
  pt_2 = {m_current_position[0] + m_width / 2.0f,
          m_current_position[1] - m_height / 2.0f,
          m_current_position[2],
          1.0f,
          0.0f,
          0.0f};
  pt_3 = {m_current_position[0] + m_width / 2.0f,
          m_current_position[1] + m_height / 2.0f,
          m_current_position[2],
          1.0f,
          0.0f,
          0.0f};
  pt_4 = {m_current_position[0] - m_width / 2.0f,
          m_current_position[1] + m_height / 2.0f,
          m_current_position[2],
          1.0f,
          0.0f,
          0.0f};

  m_vertices[0] = pt_1;
  m_vertices[1] = pt_2;
  m_vertices[2] = pt_3;
  m_vertices[3] = pt_4;

  m_indices = {0, 1, 3, 1, 2, 3};
}

std::array<Vertex, 4> Quadrilateral::get_vertices() { return m_vertices; }

std::array<unsigned int, 6> Quadrilateral::get_indices() { return m_indices; }

Quadrilateral::~Quadrilateral() {}

Circle::Circle(float starting_position[3], float radius, unsigned int res)
    : Object(starting_position), m_radius(radius), m_res(res) {}

void Circle::generate_circle() {
  m_vertices.reserve(m_res + 2);
  m_vertices.push_back({m_current_position[0], m_current_position[1],
                        m_current_position[2], 1.0f, 0.0f, 0.0f});

  float angle = 0.0f;

  for (unsigned int i = 0; i <= m_res; ++i) {
    Vertex pt;
    angle = (2 * i * PI) / m_res;

    pt.x = m_radius * std::cos(angle) + m_current_position[0];
    pt.y = m_radius * std::sin(angle) + m_current_position[1];
    pt.z = m_current_position[2];
    pt.r = 1.0f;
    pt.g = 0.0f;
    pt.b = 0.0f;

    m_vertices.push_back(pt);
    m_indices.push_back(0);
    m_indices.push_back(i);
    i == m_res ? m_indices.push_back(1) : m_indices.push_back(i + 1);
  }
}

std::vector<Vertex> Circle::get_vertices() { return m_vertices; }

std::vector<unsigned int> Circle::get_indices() { return m_indices; }

Circle::~Circle() {}
