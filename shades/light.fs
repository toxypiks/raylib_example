#version 330

in vec3 vertexPos;
in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform vec3 cameraPos;

void main() {
    //let color change when camera position does
    finalColor = gl_FragCoord;
}