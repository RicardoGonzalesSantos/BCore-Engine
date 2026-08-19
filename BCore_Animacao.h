#ifndef BCORE_ANIMACAO_H
#define BCORE_ANIMACAO_H

#include "raylib.h"

namespace bc {
    class Animador {
    public:
        ModelAnimation* animacoes = nullptr;
        int quantidade = 0;
        int frameAtual = 0;

        void Carregar(const char* caminho) {
            if (animacoes != nullptr) Encerrar();
            animacoes = LoadModelAnimations(caminho, &quantidade);
        }

        void Atualizar(Model &modelo, int indiceAnim, bool loop = true) {
            if (animacoes == nullptr || indiceAnim >= quantidade) return;

            ModelAnimation anim = animacoes[indiceAnim];
            frameAtual++;

            if (loop) {
                frameAtual %= anim.frameCount;
            } else if (frameAtual >= anim.frameCount) {
                frameAtual = anim.frameCount - 1;
            }

            UpdateModelAnimation(modelo, anim, frameAtual);
        }

        void Resetar() {
            frameAtual = 0;
        }

        void Encerrar() {
            if (animacoes != nullptr) {
                UnloadModelAnimations(animacoes, quantidade);
                animacoes = nullptr;
                quantidade = 0;
            }
        }
    };
}

#endif
