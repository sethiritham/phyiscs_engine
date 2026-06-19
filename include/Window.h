#include <../vendor/glad/include/glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
  int m_width;
  int m_height;
  const char *window_title;

  GLFWwindow *m_window;

  static void frame_buffer_size_callback(GLFWwindow *window, int width,
                                         int height) {
    glViewport(0, 0, width, height);
  }

public:
  Window(int w, int h, const char *title);

  bool should_close();

  float get_aspect_ratio();

  int get_current_width();

  int get_current_height();

  GLFWwindow *get_window();

  void swap_buffers();
  ~Window();
};
