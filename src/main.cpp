#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// function prototype
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow *window, int w, int h);

const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 600;

int main(int, char **) {
  // INITALIZE GLFW
  glfwInit();
  // TELL GLFW THAT WE ARE USING THE OPENGL VERSION 4.1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  // TELLING GLFW THAT WE USING CORE PROFILE
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // Create window with size
  GLFWwindow *window = glfwCreateWindow(
      SCR_WIDTH, SCR_HEIGHT, "My First OpenGL Application", nullptr, nullptr);

  if (window == nullptr) {
    std::cout << "Can not create window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Introduce window to current context
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 900, 600);

  // main while loop
  while (!glfwWindowShouldClose(window)) {

    processInput(window);
    
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

void framebuffer_size_callback(GLFWwindow *window, int w, int h) {
  glViewport(0, 0, w, h);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}