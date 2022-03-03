#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
uniform mat4 u_MVP;

out vec2 v_TexCoord;

void main()
{
  gl_Position = u_MVP * position;
  v_TexCoord = texCoord;
}

#shader pixel
#version 330 core

in vec2 v_TexCoord;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_Texture;

void main()
{
  vec4 texColor = texture(u_Texture, v_TexCoord);
  fragColor = texColor;          
}