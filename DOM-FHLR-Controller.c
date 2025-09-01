// DOM-FHLR-Controller.c
// 19/08/2025 - Grupo FHLR
// Fatima Franzotti Alochio
// Henrique Rosa Freire
// Luis Miguel Ravanello
// Rene Lopes da Silva

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Dom-FHLR-Controller.h"
#include "Dom-FHLR-View.c"


// Embaralha as peca
void embaralharPecas() {
    int i, j;
    Peca temp;

    srand(time(NULL));
    for (i = 0; i < totalPecas; i++) {
        j = rand() % totalPecas;
        temp = pecas[i];
        pecas[i] = pecas[j];
        pecas[j] = temp;
    }
}



//Funcao primeiro lance
int primeiroLance(){
	Peca primeiraPeca;
	primeiraPeca.ladoA = -1;
	primeiraPeca.ladoB = -1; 
	int indicePeca = 0;
	
	for(int i = 0; i < 13 ; i++){
			if((pecas[i].ladoA == pecas[i].ladoB)){
				if((pecas[i].ladoA + pecas[i].ladoB) > (primeiraPeca.ladoA + primeiraPeca.ladoB)){
					indicePeca = i;
					primeiraPeca = pecas[i];
									
				}
			} 
	}
	if(primeiraPeca.ladoA < 0){
		for(int i = 0; i < 13 ; i++){
			if((pecas[i].ladoA + pecas[i].ladoB) > (primeiraPeca.ladoA + primeiraPeca.ladoB)){
				indicePeca = i;
				primeiraPeca = pecas[i];
			}	
		}
	
	}
	
	primeiraPeca = pecas[indicePeca];
	pecas[indicePeca].status = 'M';
	// Se a primeira peca for de 0 a 6 jogadorAtual = 1, senao jogadorAtual = 2
	jogadorAtual = (indicePeca < 7) ? 1 : 2;
	
	//Adiciona a primeira peca na mesa e atualiza quantidade
	mesa[0].ladoE = primeiraPeca.ladoA;
	mesa[0].ladoD =  primeiraPeca.ladoB;
	qtdMesa++;
	return jogadorAtual; 
}

void trocarJogador(){
	if(jogadorAtual == 1){
		jogadorAtual = 2;
	}else{
		jogadorAtual = 1;
	}
}


void prepararJogo(){
	embaralharPecas();
	
	for(int i = 0; i < 28; i++){
		pecas[i].status = 0;
		mesa[i].ladoD = -1;
		mesa[i].ladoE = -1;
	}
	
	for(int i = 0; i < 7; i++){
		pecas[i].status = 1;
		pecas[i + 7].status = 2;
	}
	
	jogadorAtual = primeiroLance();
	
	printf("Primeiro Jogador: %d\n", jogadorAtual);
	apresentaMesa();
	trocarJogador();
	
}

void apresentarMenu(){
    int escolha = 0;
    while (1) {
        escolha = menuPrincipal();
        switch (escolha) {
            case 1:
                system("cls");
                jogar();
                system("pause");
                break;
            case 2:
                system("cls");
                jogar();
                system("pause");
                break;
            case 3:
                mostrarRegras();
                system("pause");
                break;
            case 0:
                printf("Saindo do jogo...\n");
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}


void jogar(){
    apresentarPecas();   
    embaralharPecas();   
    apresentarPecas(); 
    prepararJogo();
}

void iniciaJogo(){
	if(jogadorAtual > 1){
		apresentar(jogadorDois.pecas, jogadorDois.qtdPecas);
	} else{
		apresentar(jogadorUm.pecas, jogadorUm.qtdPecas);
	}
	
	//(na proxima Etapa, aqui entrara um menu para o jogador fazer a jogada, comprar peca, passar a vez, etc.) 
}

