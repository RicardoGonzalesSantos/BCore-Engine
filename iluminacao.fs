#version 330

// Entradas vindas do Vertex Shader
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;

// Saída de cor final
out vec4 finalColor;

// Uniforms
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 viewPos;
uniform float fogDensity;
uniform vec4 fogColor;
uniform vec4 ambient;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.5)); 
    
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diff * colDiffuse.rgb;
    
    // --- LINHA ATUALIZADA AQUI ---
    // Agora multiplicamos por fragColor.rgb para aceitar o "Tint" da Engine
    vec3 color = (ambient.rgb + diffuse) * texelColor.rgb * fragColor.rgb;

    // Cálculo da Neblina
    float dist = length(viewPos - fragPosition);
    float fogFactor = 1.0 / exp(dist * fogDensity);
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    finalColor = vec4(mix(fogColor.rgb, color, fogFactor), texelColor.a);
}

