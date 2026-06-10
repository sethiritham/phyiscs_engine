#include <string>

struct shaderSources {
  std::string vertexShaderSource;
  std::string fragmentShaderSource;
};

shaderSources parseShader(const char *filepath);
