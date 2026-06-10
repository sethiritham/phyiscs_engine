#include <../vendor/glad/include/glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
  Window(int w, int h, const char *title) {
    width = w;
    height = h;
    window_title = title;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, window_title, NULL, NULL);
    if (m_window == NULL) {
      std::cout << "WINDOW CREATION FAILED!" << std::endl;
      glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "GLAD FAILED!" << std::endl;
    }

    glViewport(0, 0, width, width);

    glfwSetFramebufferSizeCallback(m_window, frame_buffer_size_callback);
  }

  bool should_close() { return glfwWindowShouldClose(m_window); }

  void swap_buffers() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
  }

  ~Window() {
    if (m_window) {
      glfwDestroyWindow(m_window);
    }
    glfwTerminate();
  }
};
