#ifndef BCORE_ENTITY_H
#define BCORE_ENTITY_H

#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <string>

namespace bc {
    class Entidade {
    private:
        Matrix matrizCache;
        bool precisaRecalcular = true;

    public:
        std::string nome;
        Vector3 posicao = { 0, 0, 0 };
        Vector3 rotacao = { 0, 0, 0 };
        Vector3 escala  = { 1, 1, 1 };

        Model modelo;
        bool temModelo = false;

        Entidade* pai = nullptr;
        std::vector<Entidade*> filhos;

        Entidade(std::string n) : nome(n) {}

        ~Entidade() {
            for (auto filho : filhos) {
                if (filho != nullptr) delete filho;
            }
            filhos.clear();
        }

        void Transformar(Vector3 p, Vector3 r, Vector3 e) {
            posicao = p; rotacao = r; escala = e;
            precisaRecalcular = true;
        }

        void DefinirPai(Entidade* novoPai) {
            if (novoPai != nullptr) {
                pai = novoPai;
                pai->filhos.push_back(this);
            }
        }

        Matrix ObterMatrizGlobal() {
            if (!precisaRecalcular && pai == nullptr) return matrizCache;

            Matrix matEscala = MatrixScale(escala.x, escala.y, escala.z);
            Matrix matRotacao = QuaternionToMatrix(QuaternionFromEuler(rotacao.x * DEG2RAD,
                                                                       rotacao.y * DEG2RAD,
                                                                       rotacao.z * DEG2RAD));
            Matrix matTranslacao = MatrixTranslate(posicao.x, posicao.y, posicao.z);

            Matrix local = MatrixMultiply(MatrixMultiply(matEscala, matRotacao), matTranslacao);

            if (pai == nullptr) {
                matrizCache = local;
                precisaRecalcular = false;
                return matrizCache;
            }

            return MatrixMultiply(local, pai->ObterMatrizGlobal());
        }

        void Renderizar() {
            if (temModelo) {
                modelo.transform = ObterMatrizGlobal();
                DrawModel(modelo, {0, 0, 0}, 1.0f, WHITE);
            }

            for (auto filho : filhos) {
                if (filho != nullptr) filho->Renderizar();
            }
        }
    };
}

#endif
