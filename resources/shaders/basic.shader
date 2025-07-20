#VERTEX

#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = vec3(0.3, 0.8, 0.2);
}

#FRAGMENT

#version 330 core
in vec3 ourColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(ourColor, 1.0);
}
