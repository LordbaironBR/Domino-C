#include "view.h"
#include <stdio.h>
#include <stdlib.h> // Para system("cls") e system("clear")
#include <ctype.h>  // Para toupper()

// Limpa a tela do terminal (funciona em Windows e Linux/macOS)
void view_limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Desenha o estado completo do jogo na tela (REQ13, REQ14)
void view_desenhar_tudo(const GameState *gs) {
    view_limpar_tela();
    printf("==================== JOGO DE DOMINO ====================\n\n");

    // 1. Mostra a Mesa e as extremidades
    printf("MESA (Extremidades: %d e %d)\n", gs->extremidade_esq, gs->extremidade_dir);
    printf("  ");
    for (int i = 0; i < gs->num_pecas_mesa; i++) {
        printf("[%d|%d] ", gs->mesa[i].ladoA, gs->mesa[i].ladoB);
    }
    printf("\n\n--------------------------------------------------------\n\n");

    // 2. Mostra informacoes do oponente (escondendo as pecas)
    int oponente = (gs->jogador_atual == 1) ? 2 : 1;
    printf("Oponente (Jogador %d) tem %d pecas.\n\n", oponente, model_contar_pecas_jogador(gs, oponente));

    // 3. Mostra a mao do jogador atual com indices para selecao
    printf("Sua Mao (Jogador %d):\n", gs->jogador_atual);
    for (int i = 0; i < 28; i++) {
        if (gs->pecas[i].status == (gs->jogador_atual == 1 ? NA_MAO_J1 : NA_MAO_J2)) {
            printf("  Peca %2d: [%d|%d]\n", i + 1, gs->pecas[i].ladoA, gs->pecas[i].ladoB);
        }
    }
    printf("\n--------------------------------------------------------\n");
}

// Mostra o menu principal e retorna a escolha do usuario
int view_mostrar_menu_principal() {
    int escolha;
    view_limpar_tela();
    printf("========= BEM-VINDO AO DOMINO =========\n");
    printf("\n");
    printf("  1. Iniciar Novo Jogo (2 Jogadores)\n");
    printf("  2. Ver Regras do Jogo\n");
    printf("  0. Sair\n");
    printf("\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);
    return escolha;
}

// Mostra o menu de acoes do turno e retorna a escolha
char view_mostrar_menu_jogada(const GameState *gs) {
    char escolha;
    int pecas_no_monte = 0;
    for(int i = 0; i < 28; i++) {
        if(gs->pecas[i].status == NO_MONTE) pecas_no_monte++;
    }

    printf("MONTE: %d pecas restantes.\n", pecas_no_monte);
    printf("Turno do Jogador %d. Escolha sua acao:\n", gs->jogador_atual);
    printf("  [J]ogar uma peca\n");
    printf("  [C]omprar do monte\n");
    printf("  [P]assar a vez\n");
    printf("Sua escolha: ");
    scanf(" %c", &escolha);
    return toupper(escolha); // Retorna em maiuscula para facilitar
}

// Pergunta ao usuario qual peca ele quer jogar
int view_pegar_indice_peca(const GameState *gs) {
    int indice;
    printf("Digite o numero da peca que deseja jogar (ex: 5): ");
    scanf("%d", &indice);
    return indice;
}

// Anuncia o vencedor da partida (REQ15)
void view_anunciar_vencedor(const GameState *gs) {
    printf("\n\n!!!!!!!! FIM DE JOGO !!!!!!!!");
    switch (gs->status_jogo) {
        case VITORIA_J1:
            printf("\nO JOGADOR 1 VENCEU!\n\n");
            break;
        case VITORIA_J2:
            printf("\nO JOGADOR 2 VENCEU!\n\n");
            break;
        case EMPATE_FECHADO:
            printf("\nJOGO FECHADO! EMPATE!\n\n");
            break;
        default:
            break;
    }
}

// Mostra as regras do jogo (REQ17)
void view_mostrar_regras() {
    view_limpar_tela();
    printf("--- REGRAS BASICAS ---\n");
    printf("1. O jogo eh para 2 jogadores, cada um comeca com 7 pecas.\n");
    printf("2. O jogador com a peca dupla mais alta (6-6, 5-5, etc.) comeca a partida.\n");
    printf("3. Em seu turno, voce pode [J]ogar, [C]omprar ou [P]assar.\n");
    printf("4. Voce pode comprar quantas pecas quiser do monte antes de jogar.\n");
    printf("5. So eh permitido passar a vez se voce nao puder jogar E o monte estiver vazio.\n");
    printf("6. Vence quem jogar todas as suas pecas primeiro (bater).\n");
    printf("7. Se o jogo fechar, vence quem tiver menos pecas (ou pontos em caso de empate).\n");
    printf("\nPressione Enter para voltar ao menu...");
    while (getchar() != '\n'); // Limpa o buffer de entrada
    getchar(); // Espera o usuario pressionar Enter
}

// Funcao generica para mostrar mensagens e pausar a tela
void view_mostrar_mensagem(const char *mensagem) {
    printf("\n>>> %s <<<\n", mensagem);
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); // Limpa o buffer de entrada
    getchar(); // Espera o usuario pressionar Enter
}