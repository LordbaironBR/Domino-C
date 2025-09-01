#include "controller.h"
#include "model.h"
#include "view.h"
#include <stdio.h>

void controller_iniciar_novo_jogo() {
    GameState gs;
    model_iniciar(&gs);

    while (gs.status_jogo == JOGANDO) {
        view_desenhar_tudo(&gs);

        int turno_finalizado = 0;
        while (!turno_finalizado) {
            char escolha = view_mostrar_menu_jogada(&gs);

            switch (escolha) {
                case 'J': {
                    int indice_peca = view_pegar_indice_peca(&gs);
                    if (model_jogar_peca(&gs, indice_peca)) {
                        turno_finalizado = 1;
                    } else {
                        view_mostrar_mensagem("Jogada Invalida! Tente novamente.");
                        view_desenhar_tudo(&gs); // Redesenha a tela
                    }
                    break;
                }
                case 'C': {
                    if (!model_comprar_peca(&gs)) {
                        view_mostrar_mensagem("O monte esta vazio!");
                    }
                    view_desenhar_tudo(&gs); // Redesenha para mostrar a nova peca
                    break;
                }
                case 'P': {
                    if (model_pode_passar(&gs)) {
                        turno_finalizado = 1;
                    } else {
                        view_mostrar_mensagem("Voce nao pode passar! Ou voce pode jogar ou o monte ainda tem pecas.");
                    }
                    break;
                }
                default:
                    view_mostrar_mensagem("Opcao invalida.");
                    break;
            }
        }
        
        model_checar_fim_de_jogo(&gs);

        if (gs.status_jogo == JOGANDO) {
            model_trocar_jogador(&gs);
        }
    }
    
    view_anunciar_vencedor(&gs);
}

void controller_iniciar_sessao() {
    int sair = 0;
    while (!sair) {
        view_limpar_tela();
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
    printf("Obrigado por jogar!\n");
}