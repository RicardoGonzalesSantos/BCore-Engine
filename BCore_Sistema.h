#ifndef BCORE_SISTEMA_H
#define BCORE_SISTEMA_H

#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace bc {

    struct DadosSave {
        int faseAtual;
        Vector3 playerPos;
        float playerVida;
        int colecionaveis;
        char dataHora[20];
    };

    class Sistema {
    public:
        static bool SalvarJogo(const char* caminho, DadosSave dados) {
            std::ofstream arquivo(caminho, std::ios::binary);

            if (arquivo.is_open()) {
                arquivo.write(reinterpret_cast<char*>(&dados), sizeof(DadosSave));
                arquivo.close();
                std::cout << "BCore: jogo salvo com sucesso em " << caminho << std::endl;
                return true;
            }

            std::cerr << "BCore Erro: falha ao abrir arquivo para salvar!" << std::endl;
            return false;
        }

        static bool CarregarJogo(const char* caminho, DadosSave &dados) {
            std::ifstream arquivo(caminho, std::ios::binary);

            if (arquivo.is_open()) {
                arquivo.read(reinterpret_cast<char*>(&dados), sizeof(DadosSave));
                arquivo.close();
                std::cout << "BCore: save carregado de " << caminho << std::endl;
                return true;
            }

            std::cerr << "BCore Erro: arquivo de save nao encontrado!" << std::endl;
            return false;
        }

        static void Log(std::string mensagem) {
            std::cout << "[BCore Log]: " << mensagem << std::endl;
        }
    };
}

#endif
