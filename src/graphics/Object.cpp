#include "Object.h"
#include <array>

Triangle::Triangle(float centre[3], float width, float height,
                   TriangleTypes triangle_type)
    : m_centre{centre[0], centre[1], centre[2]}, m_width(width),
      m_height(height) {}

std::array<Vertex, 3> Triangle::generate_vertices() {
  switch (m_triangle_type) {
  case right_angle:
    m_vertices[0] = {m_centre[0], m_centre[1], m_centre[2], 1.0f, 0.0f, 0.0f};
    m_vertices[1] = {
        m_centre[0] + m_width, m_centre[1], m_centre[2], 1.0f, 0.0f, 0.0f};
    m_vertices[2] = {
        m_centre[0], m_centre[1] + m_height, m_centre[2], 1.0f, 0.0f, 0.0f};
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

Quadrilateral::Quadrilateral(float centre[3], float width, float height,
                             QuadTypes quad_type)
    : m_centre{centre[0], centre[1], centre[2]}, m_height(height),
      m_width(width), m_quad_type(quad_type) {}

Quadrilateral::Quadrilateral(float centre[3], float side, QuadTypes quad_type)
    : m_centre{centre[0], centre[1], centre[2]}, m_height(side), m_width(side),
      m_quad_type(quad_type) {}

void Quadrilateral::generate_quad() {
  Vertex pt_1;
  Vertex pt_2;
  Vertex pt_3;
  Vertex pt_4;

  pt_1 = {m_centre[0] - m_width / 2.0f,
          m_centre[1] - m_height / 2.0f,
          m_centre[2],
          1.0f,
          0.0f,
          0.0f};
  pt_2 = {m_centre[0] + m_width / 2.0f,
          m_centre[1] - m_height / 2.0f,
          m_centre[2],
          1.0f,
          0.0f,
          0.0f};
  pt_3 = {m_centre[0] + m_width / 2.0f,
          m_centre[1] + m_height / 2.0f,
          m_centre[2],
          1.0f,
          0.0f,
          0.0f};
  pt_4 = {m_centre[0] - m_width / 2.0f,
          m_centre[1] + m_height / 2.0f,
          m_centre[2],
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

std::array<int, 6> Quadrilateral::get_indices() { return m_indices; }

Quadrilateral::~Quadrilateral() {}
