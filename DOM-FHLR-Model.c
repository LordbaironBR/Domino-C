// DOM-FHLR-Model.c
// 19/08/2025 - Grupo FHLR
// Fatima Franzotti Alochio
// Henrique Rosa Freire
// Luis Miguel Ravanello
// Rene Lopes da Silva

#include "DOM-FHLR-Model.h"

Peca pecas[28];
int totalPecas = 28;
Mesa mesa[28];
int jogadorAtual = 0;
Jogador jogadorUm;
Jogador jogadorDois;
int qtdMesa = 0;

// Gera as 28 peças de domino
void gerarPecas() {
    int i, j, k = 0;
    for (i = 0; i <= 6; i++) {
        for (j = i; j <= 6; j++) {
            pecas[k].ladoA = i;
            pecas[k].ladoB = j;
            k++;
        }
    }
}

