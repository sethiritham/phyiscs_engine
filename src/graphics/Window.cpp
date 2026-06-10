#include "Window.h"
#include <iostream>

Window::Window(int w, int h, const char *title)
    : width(w), height(h), window_title(title) {
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

bool Window::should_close() { return glfwWindowShouldClose(m_window); }

void Window::swap_buffers() {
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

Window::~Window() {
  if (m_window) {
    glfwDestroyWindow(m_window);
  }
  glfwTerminate();
}
