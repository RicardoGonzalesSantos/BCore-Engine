#version 330

// Entrada vinda do Vertex Shader
in vec2 fragTexCoord;

// Textura do céu
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Saída de cor final
out vec4 finalColor;

void main()
{
    // Pega a cor da imagem nos pontos da coordenada
    vec4 texelColor = texture(texture0, fragTexCoord);
    
    // Aplica a cor da textura multiplicada por um tom (geralmente branco)
    finalColor = texelColor * colDiffuse;
}
