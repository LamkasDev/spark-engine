#version 460 core

in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D tex0;
uniform vec3 color;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex0, texCoord).r);
    FragColor = vec4(color, 1.0) * sampled;
}