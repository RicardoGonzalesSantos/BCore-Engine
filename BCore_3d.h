#ifndef BCORE_3D_H
#define BCORE_3D_H

#include "raylib.h"
#include <vector>

namespace bc {
    class Graficos3D {
    public:
        static Model CarregarModelo(const char* caminho) {
            return LoadModel(caminho);
        }

        static void AplicarTextura(Model &modelo, const char* caminho, int mapaTipo = MATERIAL_MAP_DIFFUSE) {
            Texture2D tex = LoadTexture(caminho);
            modelo.materials[0].maps[mapaTipo].texture = tex;
        }

        static void DesenharModelo(Model modelo, Vector3 posicao, float escala, Color tint = WHITE) {
            DrawModel(modelo, posicao, escala, tint);
        }

        static void DescarregarModelo(Model modelo) {
            UnloadModel(modelo);
        }
    };
}

#endif
