#ifndef BCORE_SOM_H
#define BCORE_SOM_H

#include "raylib.h"

namespace bc {
    class AudioSistema {
    public:
        static void Inicializar() {
            InitAudioDevice();
        }

        static Sound CarregarSom(const char* caminho) {
            return LoadSound(caminho);
        }

        static void TocarSom(Sound som) {
            PlaySound(som);
        }

        static Music CarregarMusica(const char* caminho) {
            return LoadMusicStream(caminho);
        }

        static void TocarMusica(Music musica) {
            PlayMusicStream(musica);
        }

        static void AtualizarMusica(Music musica) {
            UpdateMusicStream(musica);
        }

        static void DefinirVolume(Music musica, float volume) {
            SetMusicVolume(musica, volume);
        }

        static void Encerrar() {
            CloseAudioDevice();
        }
    };
}

#endif
