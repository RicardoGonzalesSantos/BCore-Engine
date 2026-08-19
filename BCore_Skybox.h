#ifndef BCORE_SKYBOX_H
#define BCORE_SKYBOX_H

#include "raylib.h"
#include "rlgl.h"

namespace bc {
    class SkyboxSistema {
    public:
        Model cuboCeu;

        void Inicializar() {
            Mesh mesh = GenMeshCube(1.0f, 1.0f, 1.0f);
            cuboCeu = LoadModelFromMesh(mesh);

            // NOTE: certifique-se de que shaders/skybox.vs e .fs existem no projeto
            cuboCeu.materials[0].shader = LoadShader("shaders/skybox.vs", "shaders/skybox.fs");
        }

        void Desenhar(Camera3D cam) {
            rlDisableDepthTest();
            rlDisableBackfaceCulling();

            Matrix matTranslation = MatrixTranslate(cam.position.x, cam.position.y, cam.position.z);
            cuboCeu.transform = matTranslation;

            DrawModel(cuboCeu, {0,0,0}, 150.0f, WHITE);

            rlEnableBackfaceCulling();
            rlEnableDepthTest();
        }

        void Encerrar() {
            UnloadModel(cuboCeu);
        }
    };
}

#endif
