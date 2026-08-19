#ifndef BCORE_ILUMINACAO_H
#define BCORE_ILUMINACAO_H

#include "raylib.h"
#include "raymath.h"

#define MAX_LUZES 4

namespace bc {
    struct Luz {
        int tipo;
        Vector3 posicao;
        Vector3 alvo;
        Color cor;
        bool ativa;
        int id;
    };

    class SistemaLuz {
    public:
        Shader shaderIluminacao = { 0 };
        int viewPosLoc = -1;
        int fogDensityLoc = -1;
        int fogColorLoc = -1;
        int ambientLoc = -1;

        void Inicializar() {
            shaderIluminacao = LoadShader("shaders/iluminacao.vs", "shaders/iluminacao.fs");

            viewPosLoc    = GetShaderLocation(shaderIluminacao, "viewPos");
            fogDensityLoc = GetShaderLocation(shaderIluminacao, "fogDensity");
            fogColorLoc   = GetShaderLocation(shaderIluminacao, "fogColor");
            ambientLoc    = GetShaderLocation(shaderIluminacao, "ambient");

            float amb[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
            SetShaderValue(shaderIluminacao, ambientLoc, amb, SHADER_UNIFORM_VEC4);

            DefinirNeblina(0.01f, BLACK);
        }

        void IluminarModelo(Model &modelo) {
            modelo.materials[0].shader = shaderIluminacao;
        }

        void Atualizar(Vector3 posCamera) {
            float cameraPos[3] = { posCamera.x, posCamera.y, posCamera.z };
            SetShaderValue(shaderIluminacao, viewPosLoc, cameraPos, SHADER_UNIFORM_VEC3);
        }

        void DefinirLuzAmbiente(Color cor) {
            float amb[4] = { (float)cor.r/255.0f, (float)cor.g/255.0f, (float)cor.b/255.0f, (float)cor.a/255.0f };
            SetShaderValue(shaderIluminacao, ambientLoc, amb, SHADER_UNIFORM_VEC4);
        }

        void DefinirNeblina(float densidade, Color cor) {
            float corFog[4] = { (float)cor.r/255.0f, (float)cor.g/255.0f, (float)cor.b/255.0f, (float)cor.a/255.0f };
            SetShaderValue(shaderIluminacao, fogDensityLoc, &densidade, SHADER_UNIFORM_FLOAT);
            SetShaderValue(shaderIluminacao, fogColorLoc, corFog, SHADER_UNIFORM_VEC4);
        }
    };
}

#endif
