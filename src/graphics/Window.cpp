#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>

Window::Window(int w, int h, const char *title)
    : m_width(w), m_height(h), window_title(title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(m_width, m_height, window_title, NULL, NULL);
  if (m_window == NULL) {
    std::cout << "WINDOW CREATION FAILED!" << std::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(m_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "GLAD FAILED!" << std::endl;
  }

  glViewport(0, 0, m_width, m_height);

  glfwSetFramebufferSizeCallback(m_window, frame_buffer_size_callback);
}

bool Window::should_close() { return glfwWindowShouldClose(m_window); }

float Window::get_aspect_ratio() {
  int height, width;

  glfwGetFramebufferSize(m_window, &width, &height);

  if (height == 0)
    height = 1;

  float aspect_ratio = (float)width / (float)height;

  return aspect_ratio;
}

void Window::swap_buffers() {
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

int Window::get_current_width() {
  glfwGetFramebufferSize(m_window, &m_width, &m_height);

  return m_width;
}

int Window::get_current_height() {
  glfwGetFramebufferSize(m_window, &m_width, &m_height);

  return m_height;
}

GLFWwindow *Window::get_window() { return m_window; }

Window::~Window() {
  if (m_window) {
    glfwDestroyWindow(m_window);
  }
  glfwTerminate();
}
