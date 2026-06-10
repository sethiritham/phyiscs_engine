#include <../vendor/glad/include/glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
  int width;
  int height;
  const char *window_title;

  GLFWwindow *m_window;

  static void frame_buffer_size_callback(GLFWwindow *window, int width,
                                         int height) {
    glViewport(0, 0, width, height);
  }

public:
  Window(int w, int h, const char *title);

  bool should_close();

  void swap_buffers();
  ~Window();
};
