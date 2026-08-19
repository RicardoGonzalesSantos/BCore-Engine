#include "BCore.h"

// Instancias globais dos sistemas que precisam sobreviver ao loop inteiro
static bc::GerenciadorAssets assets;
static bc::VideoSistema video;

int main() {
    // 1. Inicializacao do Motor
    bc::Inicializar(1280, 720, "BCore Engine - O Primeiro Passo");
    video.Inicializar();

    // 2. Preparando a Camera Emocional
    bc::CameraSistema minhaCam;
    minhaCam.Inicializar();

    // 3. Sistema de Cinema (Pos-processamento)
    bc::PosProcessamento cinema;
    cinema.Inicializar(1280, 720);
    // cinema.CarregarFiltro("shaders/ps3_grain.fs"); // Ative quando tiver o arquivo

    // 4. Carregando Ativos (3D, Som, Animacao)
    Model heroiModelo = assets.CarregarModelo("midia/heroi.glb");
    bc::Animador animHeroi;
    animHeroi.Carregar("midia/heroi.glb");

    Music trilhaSonora = bc::AudioSistema::CarregarMusica("audio/tema_triste.mp3");
    bc::AudioSistema::TocarMusica(trilhaSonora);

    // 5. Configurando o Clima (Neblina)
    bc::SistemaLuz luzes;
    luzes.Inicializar();
    luzes.DefinirNeblina(0.05f, GRAY);

    // 6. Loop Principal de Gameplay
    while (bc::Janela::Aberta()) {
        // --- LOGICA ---
        bc::AudioSistema::AtualizarMusica(trilhaSonora);
        minhaCam.Atualizar();

        Vector3 posHeroi = { 0, 0, 0 }; // Pegar posicao real depois

        if (bc::Fisica::NoGatilho(posHeroi, {10, 0, 10}, {12, 5, 12})) {
            // Carrega e comeca a tocar a cutscene ao entrar no gatilho
            if (!video.plm) {
                video.Carregar("videos/revelacao.mp4");
                video.Tocar();
            }
        }

        // --- RENDERIZACAO ---
        cinema.Iniciar(); // Comeca a gravar para o pos-processamento
            bc::Janela::LimparTela(BLACK);

            BeginMode3D(minhaCam.camera);
                animHeroi.Atualizar(heroiModelo, 0); // Ciclo Idle
                bc::Graficos3D::DesenharModelo(heroiModelo, (Vector3){0, 0, 0}, 1.0f);
            EndMode3D();

            if (video.tocando) {
                video.AtualizarEDesenhar();
            }

        cinema.Finalizar(); // Aplica o filtro e joga na tela

        bc::Janela::TerminarDesenho();
    }

    // 7. Encerramento Seguro
    video.Encerrar();
    assets.Encerrar();
    bc::Encerrar();
    return 0;
}
