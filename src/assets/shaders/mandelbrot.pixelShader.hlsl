#version 330 core

uniform float u_Time;
uniform float u_Aspect;
in vec2 v_TexCoord;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_Texture;

float rand(float x) { return fract(sin(x*(91.3458)) * 47453.5453); }

vec3 lerp(vec3 colorOne, vec3 colorTwo, float value)
{
	return ((colorOne) + value*(colorTwo-colorOne));
}

vec3 gradient(float a)  //using Ultra Fractal gradient
{
    vec3 gradientColor;
    
    vec3 color1 = vec3(0.0, 45.0, 140.0);
    vec3 color2 = vec3(240, 240, 70);
    vec3 color3 = vec3(235, 177, 70);
    vec3 color4 = vec3(232, 142, 93);
    vec3 color5 = vec3(0.0, 2.0, 0.0);
    
    if(a<0.16)
    {
        gradientColor = lerp(color1, color2, a);
        return gradientColor / 255.0;
    }
    if(a<0.42)
    {
        gradientColor = lerp(color2, color3, a);
        return gradientColor / 255.0;
    }
    if(a<0.9755)
    {
        gradientColor = lerp(color3, color4, a);
        return gradientColor / 255.0;
    }
    gradientColor = lerp(color4,color5, a);
    return gradientColor / 255.0;
}

vec3 inSet(vec2 uv, vec2 z)
{
    int i;
    for(i=0;i<1000;i++)
    {
        float uvxsq = uv.x * uv.x;
        float uvysq = uv.y * uv.y;
        float uvxy = uv.x * uv.y;
        uv = vec2(uvxsq - uvysq + z.x,  uvxy + uvxy + z.y);
        if(uvxsq + uvysq > 10000.0)
            break;
    }
    float k = float(i)/1000.0;
    return gradient(k);
}

void main()
{
  vec2 uv = -1.0 + 2.0 * v_TexCoord;
  float time = u_Time/ 1000.0;
  float zoom = (2.0/pow(2.0,time));
  
  float aspect = u_Aspect;
  uv.x *= aspect;
  vec3 col;
  
  uv *= 0.85;
  uv += vec2(-0.51, -0.61351);
  
  vec2 scaleCenter = vec2(-0.675,0.3621);
  uv = (uv - scaleCenter) * zoom + scaleCenter;
  col = inSet(vec2(0.0, 0.0), uv);
  
  fragColor = vec4(col, 1.0);        
}

//////////
