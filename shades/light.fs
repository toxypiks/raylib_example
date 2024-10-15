#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform vec3 cameraPos;

void main() {
    finalColor = mix(
        vec4(0.0, 0.0, 0.0, 1.0),
        fragColor,
        min(gl_FragCoord.w, 1.0));
}