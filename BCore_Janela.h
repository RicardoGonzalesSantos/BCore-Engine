#ifndef BCORE_JANELA_H
#define BCORE_JANELA_H

#include "raylib.h"

namespace bc {
    class Janela {
    public:
        static void Criar(int largura, int altura, const char* titulo) {
            InitWindow(largura, altura, titulo);
            SetTargetFPS(60); // Padrao PS3/PS4 para fluidez
        }

        static bool Aberta() {
            return !WindowShouldClose();
        }

        static void Fechar() {
            CloseWindow();
        }

        static void LimparTela(Color cor) {
            BeginDrawing();
            ClearBackground(cor);
        }

        static void TerminarDesenho() {
            EndDrawing();
        }
    };
}

#endif
