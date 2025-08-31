#version 330 core
out vec4 FragColor;

in vec3 color;

uniform vec3 debugColor;

void main()
{
  FragColor = vec4(debugColor, 1.0);
}