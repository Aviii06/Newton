#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 col;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec2 v_TexCoord;
out vec3 v_Color;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * vec4(position, 1.0f);
    v_TexCoord = texCoord;
    v_Color = col;
}

//////////
