# BCore Engine

> A lightweight C++ game framework built on top of [raylib](https://www.raylib.com/), aiming for a "PS3-era" aesthetic: metallic tones, punchy contrast, and a simple, readable API for small-to-medium 3D games.

BCore Engine wraps raylib with a small set of focused modules — entities, camera, lighting, animation, audio, video, physics triggers, and post-processing — so you can build a game loop quickly without losing access to plain C++ or raylib itself when you need it.

## Features

- **Entity hierarchy** — parent/child transforms with cached matrices (`bc::Entidade`)
- **Smooth camera system** — follow with lerp, screen shake (`bc::CameraSistema`)
- **Asset manager** — automatic caching of models/textures by path (`bc::GerenciadorAssets`)
- **Lighting & fog** — a basic real-time lighting shader pipeline (`bc::SistemaLuz`)
- **Animation** — looping and one-shot skeletal animation playback (`bc::Animador`)
- **Audio** — sound effects and streamed music (`bc::AudioSistema`)
- **Video cutscenes** — MPEG1 playback via [pl_mpeg](https://github.com/phoboslab/pl_mpeg), decoded on CPU into a single texture (`bc::VideoSistema`)
- **Physics triggers** — sphere collisions and AABB trigger zones (`bc::Fisica`)
- **Post-processing** — render-to-texture pipeline for screen-space filters (`bc::PosProcessamento`)
- **Map loading** — simple text-based level format, with a Blender export script included

## Project status

This project recently moved away from a macro-based "translation layer" (a Portuguese-keyword DSL like `CriarJanela`, `Enquanto`, `Inicio`/`Fim`) in favor of **plain, idiomatic C++**. All engine classes now live directly under the `bc::` namespace and are used like any normal C++ library. This makes debugging, IDE autocompletion, and onboarding new contributors much easier.

## Getting started

### 1. Dependencies

- [raylib](https://github.com/raysan5/raylib) (tested with v6.0)
- A C++17-capable compiler (GCC/MinGW, Clang, or MSVC)

### 2. Folder structure

```
YourProject/
├── BCore_Engine/          <-- Engine headers (this repo)
├── Dependencias/
│   ├── include/            <-- raylib.h, pl_mpeg.h
│   └── lib/                <-- raylib.lib / libraylib.a
├── shaders/
│   ├── iluminacao.vs
│   └── iluminacao.fs
└── main.cpp                 <-- Your game code
```

Copy `raylib.h` from `<raylib_source>/src/` into `Dependencias/include/`, and the compiled `libraylib.a` (or `raylib.lib` on MSVC) into `Dependencias/lib/`. See raylib's own build instructions if you need to compile it from source first.

### 3. Build

A ready-to-use build command is provided in [`build.txt`](build.txt) (originally written for a VS Code task bound to F6). The important flags:

```bash
g++ main.cpp -o game.exe -O2 -Wall -std=c++17 \
  -I"Dependencias/include" -I"BCore_Engine" \
  -L"Dependencias/lib" \
  -lraylib -lopengl32 -lgdi32 -lwinmm
```

> **Note:** `-std=c++17` is required — `BCore_Assets.h` uses structured bindings.

### 4. Minimal example

```cpp
#include "BCore.h"

int main() {
    bc::Inicializar(1280, 720, "My Game");

    bc::CameraSistema camera;
    camera.Inicializar();

    while (bc::Janela::Aberta()) {
        camera.Atualizar();

        bc::Janela::LimparTela(BLACK);
            BeginMode3D(camera.camera);
                DrawGrid(20, 1.0f);
            EndMode3D();
        bc::Janela::TerminarDesenho();
    }

    bc::Encerrar();
    return 0;
}
```

See [`main.cpp`](main.cpp) for a fuller example wiring up assets, animation, lighting, audio, a video cutscene trigger, and post-processing together.

## Module reference

| Module | Header | Responsibility |
|---|---|---|
| Window | `BCore_Janela.h` | Window creation, clear/present, FPS cap |
| Entities | `BCore_Entity.h` | Parent/child transform hierarchy |
| Camera | `BCore_Camera.h` | Lerp-follow camera, screen shake |
| 3D graphics | `BCore_3d.h` | Model loading & drawing |
| 2D graphics | `BCore_2d.h` | Texture/sprite drawing |
| Lighting | `BCore_Iluminacao.h` | Shader-based lighting & fog |
| Animation | `BCore_Animacao.h` | Skeletal animation playback |
| Audio | `BCore_Som.h` | SFX and streamed music |
| Video | `BCore_Video.h` | MPEG1 cutscene playback |
| Physics | `BCore_Fisica.h` | Sphere collisions, AABB triggers |
| Post-processing | `BCore_PosProcessamento.h` | Render-to-texture + fragment filters |
| Assets | `BCore_Assets.h` | Cached model/texture loading |
| Map manager | `BCore_MapManager.h` | Text-based level loading + frustum-distance culling |
| Save system | `BCore_Sistema.h` | Binary save/load |
| Skybox | `BCore_Skybox.h` | Camera-following sky cube |

## Map format

Levels are plain text files (see [`BCore_MapManager.h`](BCore_Engine/BCore_MapManager.h)):

```
// Model | PX PY PZ | RX RY RZ | Scale
column.obj 0.00 0.00 5.00 0.00 0.00 0.00 1.00
```

A Blender export script is included at [`scripts/export_bcore.py`](scripts/export_bcore.py) to generate this format from selected objects in a scene.

## Roadmap / known limitations

- Skybox shaders (`shaders/skybox.vs` / `.fs`) are not included — you'll need to provide your own.
- The video system decodes on the CPU; fine for short, low-resolution cutscenes, but not meant for full-motion video at high resolution.
- No physics broadphase beyond simple sphere/AABB checks — fine for triggers and basic collision, not a full physics engine.

## Credits

- [raylib](https://www.raylib.com/) by Ramon Santamaria and contributors (zlib/libpng license)
- [pl_mpeg](https://github.com/phoboslab/pl_mpeg) by Dominic Szablewski (MIT license)

## License

Choose a license for your own project (MIT is a common default for small engines like this) and add a `LICENSE` file at the repo root. This README does not assume one on your behalf.
