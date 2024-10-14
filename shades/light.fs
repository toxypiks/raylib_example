#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec4 fragCoord;

out vec4 finalColor;

uniform vec3 cameraPos;

void main() {
    //let color change when camera position does
    finalColor = vec4(normalize(cameraPos), 1.0);
}