#include "Object.h"

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
