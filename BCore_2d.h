#ifndef BCORE_2D_H
#define BCORE_2D_H

#include "raylib.h"

namespace bc {
    class Graficos2D {
    public:
        static Texture2D CarregarImagem(const char* caminho) {
            return LoadTexture(caminho);
        }

        static void DesenharImagem(Texture2D tex, float x, float y, Color tint = WHITE) {
            DrawTexture(tex, (int)x, (int)y, tint);
        }

        static void DesenharFrame(Texture2D tex, Rectangle frame, Vector2 pos, Color tint = WHITE) {
            DrawTextureRec(tex, frame, pos, tint);
        }
    };
}

#endif
