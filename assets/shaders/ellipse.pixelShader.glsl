#version 330 core

in vec2 v_TexCoord;
in vec3 v_Color;
layout(location = 0) out vec4 fragColor;

void main()
{
    vec2 uv = (v_TexCoord - vec2(0.5f, 0.5f)) * 2.0f;
    vec3 col = v_Color;

    float radius = 1.0f;
    float edgeBlur = 0.02f;
    float alpha = 0.0f;

    if (length(uv) < radius)
    {
        // Anti-aliased edge
        alpha = 1.0f - smoothstep(radius - edgeBlur, radius, length(uv));
    }

    fragColor = vec4(col, alpha);
}

//////////