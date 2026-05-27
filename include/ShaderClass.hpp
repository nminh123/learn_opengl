#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string get_file_contents(const char *fileName);

class Shader {
public:
  GLuint ID;
  Shader(const char *vertexFile, const char *fragmentFile);

  void Active();
  void Delete();
};
#endif