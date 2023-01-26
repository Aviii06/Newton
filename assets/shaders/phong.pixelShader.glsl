#version 330 core

in vec3 v_CrntPos;
in vec3 v_Normal;
in vec3 v_Color;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float intensity;

out vec4 FragColor;

vec4 pointLight()
{	
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPos - v_CrntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = intensity * 10.0f / dist;

	// diffuse lighting
	vec3 normal = normalize(v_Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = min(max(dot(normal, lightDirection) * inten, 0.0f), 1.0f);

	return vec4(diffuse, diffuse, diffuse, 1.0f) * vec4(lightColor, 1.0f);
}

float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float steepness, float offset)
{
	float zVal = linearizeDepth(depth);
	return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{
	// outputs final color
	float depth = logisticDepth(gl_FragCoord.z, 0.5f, 5.0f);
	FragColor = pointLight();
}

//////////
