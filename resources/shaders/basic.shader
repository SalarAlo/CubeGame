#VERTEX
#version 330 core

layout(location = 0) in vec3 i_Pos;
layout(location = 1) in vec3 i_Color;
layout(location = 2) in vec3 i_Normal;

out vec3 v_Color;
out vec3 v_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
        gl_Position = u_Projection * u_View * u_Model * vec4(i_Pos, 1.0);
        v_Color = i_Color;
        v_Normal = normalize(i_Normal);
}

#FRAGMENT

#version 330 core

struct Light {
        float Ambient;
        float Diffuse;
        float Specular;
        vec3 Color;
        vec3 Direction;
};
uniform Light u_Light;

uniform vec3 u_CameraPos;

in vec3 v_Color;
in vec3 v_Normal;

out vec4 o_FragColor;

void main() {
        vec3 N = normalize(v_Normal);
        vec3 L = normalize(-u_Light.Direction);
        vec3 V = normalize(u_CameraPos);
        vec3 R = reflect(-L, N);

        // ===== Ambient component =====
        vec3 ambient = u_Light.Ambient * u_Light.Color * v_Color;

        // ===== Diffuse component =====
        float diff = max(dot(N, L), 0.0);
        vec3 diffuse = diff * u_Light.Diffuse * u_Light.Color * v_Color;

        // ===== Specular component =====
        float spec = pow(max(dot(R, V), 0.0), 32.0);
        vec3 specular = spec * u_Light.Specular * u_Light.Color;

        // ===== Final color =====
        vec3 finalColor = ambient + diffuse + specular;
        o_FragColor = vec4(finalColor, 1.0);
}

