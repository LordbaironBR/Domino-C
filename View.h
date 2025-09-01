#ifndef VIEW_H
#define VIEW_H

#include "model.h"

// --- PROTOTIPOS DAS FUNCOES DA VISAO ---
// As funcoes da Visao APENAS leem a GameState para exibir informacoes.
// Elas nao devem modificar o estado do jogo.

void view_limpar_tela();
void view_desenhar_tudo(const GameState *gs);
int view_mostrar_menu_principal();
char view_mostrar_menu_jogada(const GameState *gs);
int view_pegar_indice_peca(const GameState *gs);
void view_anunciar_vencedor(const GameState *gs);
void view_mostrar_regras();
void view_mostrar_mensagem(const char *mensagem);

#endif