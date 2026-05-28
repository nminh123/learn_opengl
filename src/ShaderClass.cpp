#include "ShaderClass.hpp"

std::string get_file_contents(const char *fileName) {
  std::ifstream in(fileName, std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
  }
  std::cerr << "FAILED TO OPEN FILE: " << fileName << std::endl;
  throw std::runtime_error("shader file not found");
}

Shader::Shader(const char *vertexFile, const char *fragmentFile) {
  std::string vertexCode = get_file_contents(vertexFile);
  std::string fragmentCode = get_file_contents(fragmentFile);

  const char *vertexSource = vertexCode.c_str();
  const char *fragmentSource = fragmentCode.c_str();

#pragma region Create Shaders & Program
  // Muốn tạo ra một shader ta cần phải glCreateShader (dùng để tạo shader) ->
  // glShaderSource (đưa source code cho gpu để gpu tạo shader) ->
  // glCompileShader (compile shader)

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, nullptr);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
  glCompileShader(fragmentShader);

  // Kết nối (link) các shader với nhau với glCreateProgram (tạo một chương
  // trình shader) -> Gắn shaders vào chương trình shader (Attach) -> Link 2
  // shaders lại với nhau bằng glLinkShader
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  // Vì đã có 2 shader trong program, nên xoá 2 cái này.
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
#pragma endregion
}

void Shader::Active() { glUseProgram(ID); }

void Shader::Delete() { glDeleteProgram(ID); }