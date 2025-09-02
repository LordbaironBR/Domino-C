#include "model.h"
#include <stdlib.h>
#include <time.h>

// Funcao auxiliar para embaralhar
void embaralhar(Peca pecas[], int n) {
    for (int i = 0; i < n; i++) {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        Peca temp = pecas[j];
        pecas[j] = pecas[i];
        pecas[i] = temp;
    }
}

void model_iniciar(GameState *gs) {
    int k = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            gs->pecas[k].ladoA = i; gs->pecas[k].ladoB = j; gs->pecas[k].status = NO_MONTE; k++;
        }
    }
    srand(time(NULL));
    embaralhar(gs->pecas, 28);
    int distribuidas_j1 = 0, distribuidas_j2 = 0;
    for (int i = 0; i < 28; i++) {
        if (distribuidas_j1 < 7) { gs->pecas[i].status = NA_MAO_J1; distribuidas_j1++; }
        else if (distribuidas_j2 < 7) { gs->pecas[i].status = NA_MAO_J2; distribuidas_j2++; }
    }

    // Inicializacao dos indices da mesa
    gs->num_pecas_mesa = 0;
    gs->extremidade_esq = -1;
    gs->extremidade_dir = -1;
    gs->indice_esq = -1; // -1 indica que a mesa esta vazia
    gs->indice_dir = -1;
    gs->status_jogo = JOGANDO;

    model_encontrar_primeiro_jogador(gs);
}

void model_encontrar_primeiro_jogador(GameState *gs) {
    for (int i = 6; i >= 0; i--) {
        for (int k = 0; k < 28; k++) {
            if (gs->pecas[k].ladoA == i && gs->pecas[k].ladoB == i) {
                if (gs->pecas[k].status == NA_MAO_J1) {
                    gs->jogador_atual = 1;
                    model_jogar_peca(gs, k + 1, 'D');
                    model_trocar_jogador(gs);
                    return;
                }
                if (gs->pecas[k].status == NA_MAO_J2) {
                    gs->jogador_atual = 2;
                    model_jogar_peca(gs, k + 1, 'D');
                    model_trocar_jogador(gs);
                    return;
                }
            }
        }
    }
}

int model_jogar_peca(GameState *gs, int indice_peca_usuario, char lado) {
    int indice_real = indice_peca_usuario - 1;

    if (indice_real < 0 || indice_real >= 28) return 0;

    Peca *p = &gs->pecas[indice_real];
    if (p->status != (gs->jogador_atual == 1 ? NA_MAO_J1 : NA_MAO_J2)) return 0;

    Peca peca_orientada = *p;

    // Se for a primeira jogada
    if (gs->num_pecas_mesa == 0) {
        gs->extremidade_esq = p->ladoA;
        gs->extremidade_dir = p->ladoB;
        int meio = 13;
        gs->mesa[meio] = peca_orientada;
        gs->indice_esq = meio;
        gs->indice_dir = meio;
    } else {
        // Logica para jogar no lado DIREITO
        if (lado == 'D') {
            if (p->ladoA == gs->extremidade_dir) {
                gs->extremidade_dir = p->ladoB;
                peca_orientada.ladoA = p->ladoA; peca_orientada.ladoB = p->ladoB;
            } else if (p->ladoB == gs->extremidade_dir) {
                gs->extremidade_dir = p->ladoA;
                peca_orientada.ladoA = p->ladoB; peca_orientada.ladoB = p->ladoA;
            } else { return 0; }
            gs->indice_dir++;
            gs->mesa[gs->indice_dir] = peca_orientada;
        // Logica para jogar no lado ESQUERDO
        } else if (lado == 'E') {
            if (p->ladoA == gs->extremidade_esq) {
                gs->extremidade_esq = p->ladoB;
                peca_orientada.ladoA = p->ladoB; peca_orientada.ladoB = p->ladoA;
            } else if (p->ladoB == gs->extremidade_esq) {
                gs->extremidade_esq = p->ladoA;
                peca_orientada.ladoA = p->ladoA; peca_orientada.ladoB = p->ladoB;
            } else { return 0; }
            gs->indice_esq--;
            gs->mesa[gs->indice_esq] = peca_orientada;
        } else { return 0; }
    }

    p->status = NA_MESA;
    gs->num_pecas_mesa++;
    return 1;
}

int model_comprar_peca(GameState *gs) {
    for (int i = 0; i < 28; i++) {
        if (gs->pecas[i].status == NO_MONTE) {
            gs->pecas[i].status = (gs->jogador_atual == 1 ? NA_MAO_J1 : NA_MAO_J2);
            return 1;
        }
    }
    return 0;
}

int model_contar_pecas_jogador(const GameState *gs, int jogador) {
    int cont = 0;
    StatusPeca status_alvo = (jogador == 1) ? NA_MAO_J1 : NA_MAO_J2;
    for (int i = 0; i < 28; i++) {
        if (gs->pecas[i].status == status_alvo) cont++;
    }
    return cont;
}

int model_jogador_pode_jogar(const GameState *gs) {
    if(gs->num_pecas_mesa == 0) return 1;
    StatusPeca status_alvo = (gs->jogador_atual == 1) ? NA_MAO_J1 : NA_MAO_J2;
    for (int i = 0; i < 28; i++) {
        if (gs->pecas[i].status == status_alvo) {
            if (gs->pecas[i].ladoA == gs->extremidade_dir || gs->pecas[i].ladoB == gs->extremidade_dir ||
                gs->pecas[i].ladoA == gs->extremidade_esq || gs->pecas[i].ladoB == gs->extremidade_esq) {
                return 1;
            }
        }
    }
    return 0;
}

int model_pode_passar(const GameState *gs) {
    if (model_jogador_pode_jogar(gs)) return 0;
    for (int i = 0; i < 28; i++) {
        if (gs->pecas[i].status == NO_MONTE) return 0;
    }
    return 1;
}

void model_trocar_jogador(GameState *gs) {
    gs->jogador_atual = (gs->jogador_atual == 1) ? 2 : 1;
}

void model_checar_fim_de_jogo(GameState *gs) {
    if (model_contar_pecas_jogador(gs, gs->jogador_atual) == 0) {
        gs->status_jogo = (gs->jogador_atual == 1) ? VITORIA_J1 : VITORIA_J2;
        return;
    }
    int monte_vazio = 1;
    for (int i = 0; i < 28; i++) {
        if (gs->pecas[i].status == NO_MONTE) { monte_vazio = 0; break; }
    }
    if (monte_vazio) {
        int proximo_jogador = (gs->jogador_atual == 1) ? 2 : 1;
        GameState gs_simulado = *gs;
        gs_simulado.jogador_atual = proximo_jogador;
        if (!model_jogador_pode_jogar(gs) && !model_jogador_pode_jogar(&gs_simulado)) {
            int pecas_j1 = model_contar_pecas_jogador(gs, 1);
            int pecas_j2 = model_contar_pecas_jogador(gs, 2);
            if (pecas_j1 < pecas_j2) gs->status_jogo = VITORIA_J1;
            else if (pecas_j2 < pecas_j1) gs->status_jogo = VITORIA_J2;
            else gs->status_jogo = EMPATE_FECHADO;
        }
    }
}