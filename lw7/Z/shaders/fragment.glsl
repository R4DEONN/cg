#version 330 core

out vec4 FragColor;

void main() {
    vec2 uv = gl_FragCoord.xy / vec2(800, 600);
    uv = uv * 2.0 - 1.0;
    uv.x *= 800.0 / 600.0;

    float rectWidth = 0.6;
    float rectHeight = 0.4;

    bool inRect = abs(uv.x) <= rectWidth && abs(uv.y) <= rectHeight;

    float thickness = 0.05;

    float topLine = abs(uv.y - rectHeight) < thickness ? 1.0 : 0.0;

    float bottomLine = abs(uv.y + rectHeight) < thickness ? 1.0 : 0.0;

    float k = (2.0 * rectHeight) / (2.0 * rectWidth);
    float expectedY = k * uv.x;
    float diagLine = abs(uv.y - expectedY) < thickness ? 1.0 : 0.0;

    float zShape = (topLine + diagLine + bottomLine) > 0.0 && inRect ? 1.0 : 0.0;

    vec3 bgColor = vec3(0.0);
    vec3 zColor = vec3(1.0);

    vec3 finalColor = mix(bgColor, zColor, zShape);

    FragColor = vec4(finalColor, 1.0);
}