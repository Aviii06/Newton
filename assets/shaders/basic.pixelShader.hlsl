#version 330 core

in vec2 v_TexCoord;
layout(location = 0) out vec4 fragColor;

void main()
{
  vec2 uv = -1.0 + 2.0 * v_TexCoord;
  vec3 col = vec3(1.0, 0.0, 0.2); 
  fragColor = vec4(col, 1.0);        
}

//////////
