#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 bitangent;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
//TBN
out mat3 TBN;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;

    //mat3 normalMatrix = transpose(inverse(mat3(model)));
    //vec3 T = normalize(normalMatrix * aTangent);
    //vec3 N = normalize(normalMatrix * aNormal);
    //T = normalize(T - dot(T, N) * N);
    //vec3 B = cross(N, T);
    //TBN = transpose(mat3(T, B, N));
    vec3 T = normalize(vec3(model * vec4(aTangent,   0.0)));
    vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal,    0.0)));
    TBN = mat3(T, B, N);
	
    gl_Position = projection * view * vec4(FragPos, 1.0);
}