#pragma once
#include "../vendor/glad/include/glad/glad.h"
#include "glm/ext/matrix_float4x4.hpp"
#include <string>

struct shaderSources {
  std::string vertexShaderSource;
  std::string fragmentShaderSource;
};

shaderSources parseShader(const char *filepath);

class Shader {
private:
  shaderSources m_shader_sources;
  unsigned int m_vertex_shader;
  unsigned int m_fragment_shader;
  unsigned int m_shader_program;

public:
  Shader();

  void parse(const char *filepath);

  void compile_shaders();

  void attach_shaders_and_link_program();

  void use_shader_program() const;

  void set_uniform_mat4(const char *matrix_name, glm::mat4 matrix);

  void set_uniform_float(const char *float_name, float flt);

  ~Shader();
};
