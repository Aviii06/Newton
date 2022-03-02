#shader vertex
#version 330 core
in vec4 position;
void main()
{
   gl_Position = position;
}

#shader pixel
#version 330 core

out vec4 fragColor;
void main()
{
   vec3 color = vec3(99, 210, 224);
   color /= 256.0;
   fragColor = vec4(color, 1.0);
}