#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(int, char **) {
  // INITALIZE GLFW
  glfwInit();
  // TELL GLFW THAT WE ARE USING THE OPENGL VERSION 4.1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // TELLING GLFW THAT WE USING CORE PROFILE
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // Create window with size
  GLFWwindow *window = glfwCreateWindow(900, 600, "My First OpenGL Application",
                                        nullptr, nullptr);

  if (window == nullptr) {
    std::cout << "Can not create window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Introduce window to current context
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, 900, 600);

  // main while loop
  while (!glfwWindowShouldClose(window)) {

    // specify the color of the background
    glClearColor(0.07f, 0.13f, 0.2f, 1.0f);

    // clean the back buffer and assing the new color to it
    glClear(GL_COLOR_BUFFER_BIT);

    // swap the back buffer with the front buffer
    glfwSwapBuffers(window);

    // Take care of all the glfw events
    glfwPollEvents();
  }

  // Delete the window before ending program
  glfwDestroyWindow(window);
  // Terminate the GLFW before ending program
  glfwTerminate();

  return EXIT_SUCCESS;
}