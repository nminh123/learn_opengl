#version 330 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;

//Output for fragment shader
out vec3 color;

// Controls the scale of the vertices
// Sử dụng thì mới ghi vào, không thì xoá đi, không nó lỗi.
uniform float scale;

void main()
{
    // Outputs the positions/coordinates of all vertices
    gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    // Assigns the colors from the Vertex Data to "color"
    color = aColor;
}