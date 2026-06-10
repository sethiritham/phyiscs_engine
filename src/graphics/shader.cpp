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
