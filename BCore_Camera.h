#ifndef BCORE_CAMERA_H
#define BCORE_CAMERA_H

#include "raylib.h"
#include "raymath.h"

namespace bc {
    class CameraSistema {
    private:
        Vector3 alvoSuave;
        float forcaTremor;

    public:
        Camera3D camera;

        void Inicializar() {
            camera = { 0 };
            camera.position = { 10.0f, 10.0f, 10.0f };
            camera.target = { 0.0f, 0.0f, 0.0f };
            camera.up = { 0.0f, 1.0f, 0.0f };
            camera.fovy = 45.0f;
            camera.projection = CAMERA_PERSPECTIVE;
            alvoSuave = camera.target;
            forcaTremor = 0.0f;
        }

        void Seguir(Vector3 destino, float suavidade) {
            camera.target = Vector3Lerp(camera.target, destino, suavidade);
        }

        void Tremer(float intensidade) {
            forcaTremor = intensidade;
        }

        void Atualizar() {
            if (forcaTremor > 0) {
                camera.position.x += GetRandomValue(-100, 100) * 0.001f * forcaTremor;
                camera.position.y += GetRandomValue(-100, 100) * 0.001f * forcaTremor;
                forcaTremor *= 0.9f;
                if (forcaTremor < 0.1f) forcaTremor = 0;
            }
        }
    };
}

#endif
