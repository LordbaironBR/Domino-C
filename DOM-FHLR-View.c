// DOM-FHLR-View.c
// 19/08/2025 - Grupo FHLR
// Fatima Franzotti Alochio
// Henrique Rosa Freire
// Luis Miguel Ravanello
// Rene Lopes da Silva

#include <stdio.h>
#include "DOM-FHLR-View.h"
//#include "DOM-FHLR-Model.c"



void apresentarPecas() {
    int i;
    printf("\n--- Pecas de Domino ---\n");
    for (i = 0; i < 28; i++) {
        printf("[%d|%d] ", pecas[i].ladoA, pecas[i].ladoB);
        if ((i + 1) % 7 == 0) {
            printf("\n"); 
        }
    }
    printf("\n");
}

void apresentar(Peca pecas[], int tam){
	for(int i = 0; i < tam; i++){
		printf("[%d|%d] ", pecas[i].ladoA, pecas[i].ladoB);
	}
}

void apresentaMesa(){
	for(int i = 0; i < qtdMesa; i++){
		printf("MESA");
		printf("[ %d | %d ] - ", mesa[i].ladoE, mesa[i].ladoD);
	}
}

void mostrarRegras()
{
	system("cls");
	printf("REGRAS DO DOMINO:\n");
	printf("1) Cada jogador recebera 7 pecas.\n2) O jogador com a peca de maior duplo (ex: 6-6) comeca a partida, colocando-a no centro da mesa.\n");
	printf("3) Caso nao tenha peca para jogar o jogador comprarar uma peca da banca.\n4) Ganha quem remover todas as pecas de seu inventario.\n");
	
	system("pause");
}

int menuPrincipal()
{
	int escolha;
	system("cls");
	printf("========================================================================================================");
	printf("\nDomino:\n");
	printf(" 1- Modo Jogador vs Jogador ;\n 2- Modo Jogador vs CPU;\n 3- Regras;\n 0- Sair;\n\nESCOLHA: ");
	scanf("%d", &escolha);
	return escolha;	
}

void apresentaMensagem(char mens[100]) {
	printf("%s\n", mens);
}
