// DOM-FHLR-Model.h
// 19/08/2025 - Grupo FHLR
// Fatima Franzotti Alochio
// Henrique Rosa Freire
// Luis Miguel Ravanello
// Rene Lopes da Silva



// Estrutura peca de domino
typedef struct{
    int ladoA;
    int ladoB;
    char status;
}Peca;

//Estrutura da mesa
typedef struct {
	int ladoE;
	int ladoD;
}Mesa;

typedef struct {
	Peca pecas[28];
	int qtdPecas;
	int numero;
}Jogador;

// Variaveis globais
extern Peca pecas[28];
extern int totalPecas;
extern Mesa mesa[28];

extern Jogador jogadorUm;
extern Jogador jogadorDois;

extern int mesaE, mesaD;
extern int qtdMesa;
extern int jogadorAtual;



