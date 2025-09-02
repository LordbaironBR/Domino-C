#include "controller.h"
#include "model.h"
#include "view.h"
#include <stdio.h>

// Funcao que gerencia uma partida completa, do inicio ao fim
void controller_iniciar_novo_jogo() {
    GameState gs;
    // Prepara o jogo: cria pecas, embaralha, distribui,
    // encontra o primeiro jogador, faz a primeira jogada e ja troca o turno.
    model_iniciar(&gs);

    // Loop principal do jogo: continua enquanto o status for "JOGANDO"
    while (gs.status_jogo == JOGANDO) {

        // No inicio de cada turno, desenha a tela para o jogador atual
        view_desenhar_tudo(&gs);

        int turno_finalizado = 0;
        // Loop do turno: continua ate o jogador fazer uma acao valida (Jogar ou Passar)
        while (!turno_finalizado) {
            char escolha = view_mostrar_menu_jogada(&gs);

            switch (escolha) {
                case 'J': {
                    int indice_peca = view_pegar_indice_peca(&gs);
                    if (model_jogar_peca(&gs, indice_peca)) {
                        turno_finalizado = 1; // Jogada valida, encerra o turno
                    } else {
                        view_mostrar_mensagem("Jogada Invalida! Tente novamente.");
                        view_desenhar_tudo(&gs); // Redesenha a tela para nova tentativa
                    }
                    break;
                }
                case 'C': { // REQ16: Comprar pecas
                    if (!model_comprar_peca(&gs)) {
                        view_mostrar_mensagem("O monte esta vazio!");
                    }
                    // Apos comprar, o turno continua, entao apenas redesenhamos a tela
                    view_desenhar_tudo(&gs);
                    break;
                }
                case 'P': {
                    if (model_pode_passar(&gs)) {
                        turno_finalizado = 1; // Passou a vez, encerra o turno
                    } else {
                        view_mostrar_mensagem("Voce nao pode passar! Ou voce pode jogar ou o monte ainda tem pecas.");
                    }
                    break;
                }
                default:
                    view_mostrar_mensagem("Opcao invalida. Pressione J, C ou P.");
                    break;
            }
        }

        // Apos o fim do turno, verifica se o jogo acabou
        model_checar_fim_de_jogo(&gs);

        // Se o jogo ainda nao acabou, passa a vez para o proximo jogador
        if (gs.status_jogo == JOGANDO) {
            model_trocar_jogador(&gs);
        }
    }

    // O loop terminou, o jogo acabou. Mostra a mesa final e anuncia o vencedor.
    view_desenhar_tudo(&gs);
    view_anunciar_vencedor(&gs);
}

// Funcao que gerencia a sessao inteira do programa (menu principal)
void controller_iniciar_sessao() {
    int sair = 0;
    while (!sair) {
        int escolha = view_mostrar_menu_principal();
        switch (escolha) {
            case 1:
                controller_iniciar_novo_jogo();
                view_mostrar_mensagem("Jogo finalizado. Voltando ao menu principal.");
                break;
            case 2:
                view_mostrar_regras();
                break;
            case 0:
                sair = 1;
                break;
            default:
                view_mostrar_mensagem("Opcao invalida.");
                break;
        }
    }
    printf("\nObrigado por jogar!\n");
}