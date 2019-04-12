#version 150

uniform mat4 transform, camera, projection;

in vec3 position, normal;
in vec2 uv;


void main() {
    mat4 modelview = camera * transform;
    vec4 eye_position = modelview * vec4(position, 1.0);
    gl_Position = projection * eye_position;
}