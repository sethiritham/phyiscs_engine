#pragma once
#include "../vendor/glad/include/glad/glad.h"
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

  ~Shader();
};
