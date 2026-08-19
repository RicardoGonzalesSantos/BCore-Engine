#ifndef BCORE_ASSETS_H
#define BCORE_ASSETS_H

#include "raylib.h"
#include <map>
#include <string>

namespace bc {
    // NOTE: usa structured bindings (C++17). Compile com -std=c++17.
    class GerenciadorAssets {
    private:
        std::map<std::string, Model> modelos;
        std::map<std::string, Texture2D> texturas;

    public:
        Model CarregarModelo(const char* caminho) {
            if (modelos.find(caminho) == modelos.end()) {
                modelos[caminho] = LoadModel(caminho);
            }
            return modelos[caminho];
        }

        Texture2D CarregarTextura(const char* caminho) {
            if (texturas.find(caminho) == texturas.end()) {
                texturas[caminho] = LoadTexture(caminho);
            }
            return texturas[caminho];
        }

        void Encerrar() {
            for (auto const& [caminho, m] : modelos) UnloadModel(m);
            for (auto const& [caminho, t] : texturas) UnloadTexture(t);
            modelos.clear();
            texturas.clear();
        }
    };
}

#endif
