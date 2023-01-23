#version 330 core

in vec2 v_TexCoord;
in vec3 v_Color;
layout(location = 0) out vec4 fragColor;

void main()
{
    vec2 uv = v_TexCoord;
    vec3 col = v_Color;

    float thickness = 0.02f;
    float alpha = 0.0f;

    if (uv.x + thickness > uv.y && uv.x - thickness < uv.y)
    {
        // Anti-aliased edge
        alpha = 1.0f - abs(uv.x - uv.y) / thickness;
    }

    fragColor = vec4(col, alpha);
}

//////////