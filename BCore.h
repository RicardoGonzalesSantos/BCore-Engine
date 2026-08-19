#ifndef BCORE_H
#define BCORE_H

// --- Core Libraries ---
#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>

// --- BCore Engine Modules ---
#include "BCore_Janela.h"
#include "BCore_3d.h"
#include "BCore_2d.h"
#include "BCore_Entity.h"
#include "BCore_Camera.h"
#include "BCore_Fisica.h"
#include "BCore_Iluminacao.h"
#include "BCore_Som.h"
#include "BCore_Animacao.h"
#include "BCore_Assets.h"
#include "BCore_Video.h"
#include "BCore_Sistema.h"
#include "BCore_MapManager.h"
#include "BCore_PosProcessamento.h" // FIX: nome de arquivo corrigido (era "BCore_Pos.h")
#include "BCore_Skybox.h"

namespace bc {

    // Inicializacao global da engine (janela + audio)
    inline void Inicializar(int largura, int altura, const char* titulo) {
        bc::Janela::Criar(largura, altura, titulo);
        SetTargetFPS(60);

        bc::AudioSistema::Inicializar();

        std::cout << "BCore Engine: sistema inicializado com sucesso." << std::endl;
        std::cout << "Modo: PS3 Aesthetic / High Performance." << std::endl;
    }

    inline void Encerrar() {
        bc::AudioSistema::Encerrar(); // Importante: desliga o audio primeiro
        bc::Janela::Fechar();
        std::cout << "BCore Engine: sistema encerrado." << std::endl;
    }

} // namespace bc

#endif // BCORE_H
