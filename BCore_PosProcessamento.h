#ifndef BCORE_POS_H
#define BCORE_POS_H

#include "raylib.h"

namespace bc {
    class PosProcessamento {
    public:
        RenderTexture2D alvo = { 0 };
        Shader shaderEfeito = { 0 };
        bool ativo = false;

        // Inicializa a textura onde o jogo sera desenhado
        void Inicializar(int largura, int altura) {
            alvo = LoadRenderTexture(largura, altura);
        }

        // Carrega um filtro especifico (ex: shaders/bloom.fs)
        void CarregarFiltro(const char* caminhoFragment) {
            shaderEfeito = LoadShader(0, caminhoFragment);
            ativo = true;
        }

        // Comeca a desenhar na textura (tudo entre Iniciar/Finalizar recebe o filtro)
        // FIX: renomeado de "Começar" para "Iniciar" (identificador ASCII-safe)
        void Iniciar() {
            BeginTextureMode(alvo);
        }

        // Termina e aplica o efeito na tela principal
        void Finalizar() {
            EndTextureMode();

            if (ativo) BeginShaderMode(shaderEfeito);

            // Desenha a textura na tela (invertida verticalmente por padrao da GPU)
            DrawTextureRec(alvo.texture,
                (Rectangle){ 0, 0, (float)alvo.texture.width, (float)-alvo.texture.height },
                (Vector2){ 0, 0 }, WHITE);

            if (ativo) EndShaderMode();
        }

        void Encerrar() {
            UnloadRenderTexture(alvo);
            if (ativo) UnloadShader(shaderEfeito);
        }
    };
}

#endif
