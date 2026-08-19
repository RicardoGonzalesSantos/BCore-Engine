#ifndef BCORE_FISICA_H
#define BCORE_FISICA_H

#include "raylib.h"
#include "raymath.h"

namespace bc {
class Fisica {
public:
    static bool ColisaoEsferas(Vector3 p1, float r1, Vector3 p2, float r2) {
        return CheckCollisionSpheres(p1, r1, p2, r2);
    }

    static float ObterAlturaSolo(Vector3 posPlayer, Model mapa, bool &colidiu) {
        Ray raio = { (Vector3){ posPlayer.x, posPlayer.y + 10.0f, posPlayer.z }, (Vector3){ 0, -1, 0 } };
        RayCollision hit = GetRayCollisionMesh(raio, mapa.meshes[0], MatrixIdentity());
        colidiu = hit.hit;
        return hit.point.y;
    }

    static bool NoGatilho(Vector3 pos, Vector3 min, Vector3 max) {
        return (pos.x >= min.x && pos.x <= max.x &&
                pos.y >= min.y && pos.y <= max.y &&
                pos.z >= min.z && pos.z <= max.z);
    }

    static bool PontoVisivel(Camera3D cam, Vector3 alvo, float margem = 0.2f) {
        Vector3 dirAlvo = Vector3Normalize(Vector3Subtract(alvo, cam.position));
        Vector3 dirCam = Vector3Normalize(Vector3Subtract(cam.target, cam.position));
        return Vector3DotProduct(dirCam, dirAlvo) > margem;
    }
};
}

#endif
