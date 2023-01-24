#version 330 core

in vec2 v_TexCoord;
in vec3 v_Color;
layout(location = 0) out vec4 fragColor;

void main()
{
    vec2 uv = -1.0 + 2.0 * v_TexCoord;
    vec3 col = v_Color;
    fragColor = vec4(col, 1.0f);
}

//////////
