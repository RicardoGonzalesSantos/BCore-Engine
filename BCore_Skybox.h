#ifndef BCORE_SKYBOX_H
#define BCORE_SKYBOX_H

#include "raylib.h"
#include "rlgl.h"

namespace bc {
    class SkyboxSystem {
    public:
        Model skyboxCube;

        void Initialize() {
            Mesh mesh = GenMeshCube(1.0f, 1.0f, 1.0f);
            skyboxCube = LoadModelFromMesh(mesh);

            // NOTE: Make sure shaders/skybox.vs and .fs exist in your project
            skyboxCube.materials[0].shader = LoadShader("shaders/skybox.vs", "shaders/skybox.fs");
        }

        void Draw(Camera3D cam) {
            rlDisableDepthTest();
            rlDisableBackfaceCulling();

            Matrix matTranslation = MatrixTranslate(cam.position.x, cam.position.y, cam.position.z);
            skyboxCube.transform = matTranslation;

            DrawModel(skyboxCube, {0,0,0}, 150.0f, WHITE);

            rlEnableBackfaceCulling();
            rlEnableDepthTest();
        }

        void Shutdown() {
            UnloadModel(skyboxCube);
        }
    };
}

#endif
