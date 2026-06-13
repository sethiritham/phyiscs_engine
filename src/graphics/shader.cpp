#include "shader.h"
#include <fstream>
#include <sstream>

shaderSources parseShader(const char *filepath) {
  std::ifstream stream(filepath);

  enum class shaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

  std::string line;

  std::stringstream ss[2];

  shaderType type = shaderType::NONE;

  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = shaderType::VERTEX;
      }

      else if (line.find("fragment") != std::string::npos) {
        type = shaderType::FRAGMENT;
      }
    } else {
      ss[(int)type] << line << '\n';
    }
  }

  shaderSources sources;
  sources.vertexShaderSource = ss[0].str();
  sources.fragmentShaderSource = ss[1].str();

  return sources;
}

Shader::Shader() {
  m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  m_shader_program = glCreateProgram();
}

void Shader::parse(const char *filepath) {
  std::ifstream stream(filepath);

  enum class shaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

  std::string line;

  std::stringstream ss[2];

  shaderType type = shaderType::NONE;

  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = shaderType::VERTEX;
      }

      else if (line.find("fragment") != std::string::npos) {
        type = shaderType::FRAGMENT;
      }
    } else {
      ss[(int)type] << line << '\n';
    }
  }

  m_shader_sources.vertexShaderSource = ss[0].str();
  m_shader_sources.fragmentShaderSource = ss[1].str();
}

void Shader::compile_shaders() {
  const char *vertex_shader_source =
      m_shader_sources.vertexShaderSource.c_str();
  const char *fragment_shader_source =
      m_shader_sources.fragmentShaderSource.c_str();

  glShaderSource(m_vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(m_vertex_shader);

  glShaderSource(m_fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(m_fragment_shader);
}

void Shader::attach_shaders_and_link_program() {
  glAttachShader(m_shader_program, m_vertex_shader);
  glAttachShader(m_shader_program, m_fragment_shader);
  glLinkProgram(m_shader_program);
}

void Shader::use_shader_program() const { glUseProgram(m_shader_program); }

void Shader::set_uniform_mat4(const char *matrix_name, glm::mat4 matrix) {
  unsigned int location = glGetUniformLocation(m_shader_program, matrix_name);

  glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

Shader::~Shader() {
  glDeleteShader(m_fragment_shader);
  glDeleteShader(m_vertex_shader);
  glDeleteProgram(m_shader_program);
}
