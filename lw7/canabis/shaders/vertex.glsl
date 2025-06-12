#version 330 core

layout(location = 0) in float x;

void main() {
    float scale = 0.4;
    float R = (1.0 + sin(x)) *
              (1.0 + 0.9 * cos(8.0 * x)) *
              (1.0 + 0.1 * cos(24.0 * x)) *
              (0.5 + 0.05 * cos(340.0 * x));

    float x_prime = R * cos(x);
    float y_prime = R * sin(x);

    gl_Position = vec4(x_prime * scale, y_prime * scale, 0.0, 1.0);
}