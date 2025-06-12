#version 330 core

layout(location = 0) in vec2 uv;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 vUV;

const float PI = 3.141592653589793;

float t = abs(sin(time));

vec3 sphere(float u, float v)
{
    float theta = u * 2.0 * PI;
    float phi = v * PI - PI / 2.0;

    return vec3(
        cos(phi) * cos(theta),
        cos(phi) * sin(theta),
        sin(phi)
    );
}

vec3 torus(float u, float v)
{
    float r = 0.6;
    float R = 1.0;

    float theta = u * 2.0 * PI;
    float phi = (v - 0.5) * 2.0 * PI;

    return vec3(
        (R + r * cos(phi)) * cos(theta),
        (R + r * cos(phi)) * sin(theta),
        r * sin(phi)
    );
}

vec3 morph(float u, float v, float t)
{
    return mix(sphere(u, v), torus(u, v), t);
}

vec3 computeNormal(float u, float v, float t)
{
    float h = 0.001;
    vec3 p = morph(u, v, t);
    vec3 dx = morph(u + h,1 v, t) - p;
    vec3 dy = morph(u, v + h, t) - p;
    return normalize(cross(dx, dy));
}

void main()
{
    float u = uv.x;
    float v = uv.y;

    vec3 pos = morph(u, v, t);
    vec4 worldPos = model * vec4(pos, 1.0);

    gl_Position = projection * view * worldPos;

    fragPos = worldPos.xyz;
    fragNormal = computeNormal(u, v, t);
    vUV = uv;
}