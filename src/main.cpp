#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

#include "EBO.hpp"
#include "ShaderClass.hpp"
#include "VAO.hpp"
#include "VBO.hpp"

// function prototype
#pragma region function prototype
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int w, int h);
#pragma endregion

// #pragma region shader
// const char *vertexShaderSource =
//     "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "}\0";
// const char *fragmentShaderSource =
//     "#version 330 core\n"
//     "out vec4 FragColor;\n"
//     "void main()\n"
//     "{\n"
//     "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//     "}\n\0";
// #pragma endregion

GLfloat vertices[] = {
    -.5f,     -.5f * float(sqrt(3)) / 3,     0.0f,
    .5f,      -.5f * float(sqrt(3)) / 3,     0.0f,
    0.0f,     0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
    -.5f / 2, .5f * float(sqrt(3)) / 6,      0.0f,
    .5f / 2,  .5f * float(sqrt(3)) / 6,      0.0f,
    0.0f,     -.5f * float(sqrt(3)) / 6,     0.0f //
};

GLuint indices[] = {
    0, 3, 5, // lower left triangle
    3, 2, 4, // lower right triangle
    5, 4, 1  // upper triangle
};

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

  const unsigned int SCR_WIDTH = 800;
  const unsigned int SCR_HEIGHT = 600;
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

  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

  // #pragma region Create Shaders & Program
  //   // Muốn tạo ra một shader ta cần phải glCreateShader (dùng để tạo shader)
  //   ->
  //   // glShaderSource (đưa source code cho gpu để gpu tạo shader) ->
  //   // glCompileShader (compile shader)

  //   GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  //   glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  //   glCompileShader(vertexShader);

  //   GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  //   glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  //   glCompileShader(fragmentShader);

  //   // Kết nối (link) các shader với nhau với glCreateProgram (tạo một chương
  //   // trình shader) -> Gắn shaders vào chương trình shader (Attach) -> Link
  //   2
  //   // shaders lại với nhau bằng glLinkShader
  //   GLuint shaderProgram = glCreateProgram();
  //   glAttachShader(shaderProgram, vertexShader);
  //   glAttachShader(shaderProgram, fragmentShader);
  //   glLinkProgram(shaderProgram);

  //   // Vì đã có 2 shader trong program, nên xoá 2 cái này.
  //   glDeleteShader(vertexShader);
  //   glDeleteShader(fragmentShader);
  // #pragma endregion

  Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

  /*
  Buffer là gì? Khi chuyển thông tin (data) từ cpu -> gpu khá chậm nên phải gom
  nhiều data gửi luôn một lần. Cái đó gọi là buffer VBO: Vertex Buffer Object

  VAO: Vertex Array Object
  */
  // GLuint VAO, VBO, EBO;
  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);
  // glGenBuffers(1, &EBO);

  // glBindVertexArray(VAO);

  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
  // GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void
  // *)0); glEnableVertexAttribArray(0);

  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindVertexArray(0);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  VAO VAO1;
  VAO1.Bind();

  VBO VBO1(vertices, sizeof(vertices));
  EBO EBO1(indices, sizeof(indices));

  VAO1.LinkVBO(VBO1, 0);
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  // main while loop
  while (!glfwWindowShouldClose(window)) {

    processInput(window);

    // specify the color of the background
    glClearColor(0.07f, 0.13f, 0.2f, 1.0f);

    // clean the back buffer and assing the new color to it
    glClear(GL_COLOR_BUFFER_BIT);

    // glUseProgram(shaderProgram);
    shaderProgram.Active();
    VAO1.Bind();
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    // swap the back buffer with the front buffer
    glfwSwapBuffers(window);

    // Take care of all the glfw events
    glfwPollEvents();
  }

  // glDeleteVertexArrays(1, &VAO);
  VAO1.Delete();
  // glDeleteBuffers(1, &VBO);
  VBO1.Delete();
  // glDeleteBuffers(1, &EBO);
  EBO1.Delete();
  // glDeleteProgram(shaderProgram);
  shaderProgram.Delete();

  // Delete the window before ending program
  glfwDestroyWindow(window);
  // Terminate the GLFW before ending program
  glfwTerminate();

  return EXIT_SUCCESS;
}

// Param thứ 2 của phương thức glfwSetFramebufferSizeCallback
// typedef void (*)(GLFWwindow* window, int width, int height)
void framebuffer_size_callback(GLFWwindow *window, int w, int h) {
  glViewport(0, 0, w, h);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}