#version 330 core

in vec3 fragNormal;
in vec3 fragPos;
in vec2 vUV;

out vec4 outColor;

uniform vec3 lightPos = vec3(2.0, 2.0, 2.0);
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 objectColor = vec3(0.3, 0.6, 0.9);

float checkerPattern(vec2 uv)
{
    float frequency = 10.0;

    int x = int(floor(uv.x * frequency));
    int y = int(floor(uv.y * frequency));

    bool isBlack = (x % 2 == y % 2);

    return isBlack ? 0.6 : 0.8;
}

void main()
{
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float brightness = checkerPattern(vUV);
    vec3 finalColor = diffuse * objectColor * brightness;
    outColor = vec4(finalColor, 1.0);
}