#ifndef BCORE_VIDEO_H
#define BCORE_VIDEO_H

#include "raylib.h"

#define PL_MPEG_IMPLEMENTATION
#include "pl_mpeg.h"

#include <cstdlib>

namespace bc {

    // Sistema de video simplificado.
    // Decodifica MPEG1 (via pl_mpeg) na CPU e converte YUV->RGB com
    // plm_frame_to_rgb(), atualizando uma unica textura por frame.
    // Mais simples e mais leve que o pipeline anterior com shader YUV
    // (3 texturas + shader customizado), ideal para cutscenes curtas
    // em baixa resolucao (estetica retro).
    class VideoSistema {
    private:
        Texture2D texVideo = { 0 };
        unsigned char* bufferRGB = nullptr;
        int largura = 0;
        int altura = 0;

    public:
        plm_t* plm = nullptr;
        bool tocando = false;

        // Nao ha shader para inicializar nesta versao; mantido por
        // compatibilidade de API com o resto da engine.
        void Inicializar() {}

        void Carregar(const char* caminho) {
            Descarregar(); // Libera video anterior, se houver

            plm = plm_create_with_filename(caminho);
            if (!plm) {
                TraceLog(LOG_WARNING, "BCore_Video: falha ao abrir '%s'", caminho);
                return;
            }

            // Audio do video e ignorado aqui de proposito: use
            // bc::AudioSistema (Music/Sound) para trilha e dublagem.
            plm_set_audio_enabled(plm, FALSE);
            plm_set_loop(plm, FALSE);

            largura = plm_get_width(plm);
            altura  = plm_get_height(plm);

            bufferRGB = (unsigned char*)malloc((size_t)largura * altura * 3);

            Image im = GenImageColor(largura, altura, BLACK);
            ImageFormat(&im, PIXELFORMAT_UNCOMPRESSED_R8G8B8);
            texVideo = LoadTextureFromImage(im);
            UnloadImage(im);
        }

        void Tocar() { tocando = true; }
        void Pausar() { tocando = false; }

        // Decodifica o proximo frame (se necessario) e desenha na tela cheia.
        void AtualizarEDesenhar() {
            if (!plm || !tocando) return;

            plm_frame_t* frame = plm_decode_video(plm);
            if (frame && bufferRGB) {
                plm_frame_to_rgb(frame, bufferRGB, frame->width * 3);
                UpdateTexture(texVideo, bufferRGB);
            }

            DrawTexturePro(
                texVideo,
                (Rectangle){ 0, 0, (float)texVideo.width, (float)texVideo.height },
                (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
                (Vector2){ 0, 0 }, 0.0f, WHITE
            );

            if (plm_has_ended(plm)) tocando = false;
        }

        bool Terminou() const { return plm && plm_has_ended(plm); }

        void Descarregar() {
            if (plm) {
                plm_destroy(plm);
                plm = nullptr;
            }
            if (bufferRGB) {
                free(bufferRGB);
                bufferRGB = nullptr;
            }
            if (texVideo.id != 0) {
                UnloadTexture(texVideo);
                texVideo = (Texture2D){ 0 };
            }
            tocando = false;
        }

        void Encerrar() {
            Descarregar();
        }
    };
}

#endif
