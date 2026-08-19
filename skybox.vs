#version 330

// Atributos de entrada
in vec3 vertexPosition;
in vec2 vertexTexCoord;

// Uniforms (dados vindos do C++)
uniform mat4 mvp;

// Saída para o Fragment Shader
out vec2 fragTexCoord;

void main()
{
    fragTexCoord = vertexTexCoord;
    
    // Calcula a posição final do vértice na tela
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
