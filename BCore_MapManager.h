#ifndef BCORE_MAPMANAGER_H
#define BCORE_MAPMANAGER_H

#include "raylib.h"
#include "raymath.h"
#include "BCore_Entity.h"
#include "BCore_Assets.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace bc {
    class MapManager {
    public:
        std::vector<Entidade*> entidadesDaFase;

        void CarregarMapa(const char* caminho, GerenciadorAssets& assets) {
            LimparFase();
            std::ifstream arquivo(caminho);
            std::string linha;

            if (!arquivo.is_open()) {
                std::cout << "BCore Erro: falha ao abrir mapa: " << caminho << std::endl;
                return;
            }

            while (std::getline(arquivo, linha)) {
                if (linha.empty() || linha.substr(0, 2) == "//") continue;

                std::stringstream ss(linha);
                std::string nomeModelo;
                float px, py, pz, rx, ry, rz, escala;

                if (ss >> nomeModelo >> px >> py >> pz >> rx >> ry >> rz >> escala) {
                    Entidade* novaEnt = new Entidade(nomeModelo);
                    novaEnt->modelo = assets.CarregarModelo(nomeModelo.c_str());
                    novaEnt->temModelo = true;
                    novaEnt->Transformar({px, py, pz}, {rx, ry, rz}, {escala, escala, escala});
                    entidadesDaFase.push_back(novaEnt);
                }
            }
            arquivo.close();
        }

        void RenderizarFaseOtimizada(Camera3D camera, float distMax) {
            for (auto ent : entidadesDaFase) {
                if (ent == nullptr) continue;

                float d = Vector3Distance(camera.position, ent->posicao);

                Vector3 paraEnt = Vector3Normalize(Vector3Subtract(ent->posicao, camera.position));
                Vector3 frenteCam = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
                float dot = Vector3DotProduct(frenteCam, paraEnt);

                if (d < distMax && dot > 0.2f) {
                    ent->Renderizar();
                }
            }
        }

        void LimparFase() {
            for (auto ent : entidadesDaFase) {
                if (ent != nullptr) delete ent;
            }
            entidadesDaFase.clear();
        }
    };
}

#endif
