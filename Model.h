#ifndef MODEL_H
#define MODEL_H

// Enum para o status da peca, mais legivel que chars ou ints
typedef enum {
    NO_MONTE,
    NA_MAO_J1,
    NA_MAO_J2,
    NA_MESA
} StatusPeca;

// Enum para o status do jogo
typedef enum {
    JOGANDO,
    VITORIA_J1,
    VITORIA_J2,
    EMPATE_FECHADO
} StatusJogo;

// Estrutura para uma peca de domino
typedef struct {
    int ladoA;
    int ladoB;
    StatusPeca status;
} Peca;

// A struct principal que contem TODO o estado do jogo
typedef struct {
    Peca pecas[28];
    Peca mesa[28]; // Array para a representacao visual da mesa
    int num_pecas_mesa;
    int extremidade_esq;
    int extremidade_dir;

    // Indices para controlar o array da mesa como uma fila de duas pontas
    int indice_esq;
    int indice_dir;

    int jogador_atual; // 1 para Jogador 1, 2 para Jogador 2
    StatusJogo status_jogo;
} GameState;

// --- PROTOTIPOS DAS FUNCOES DO MODELO ---

void model_iniciar(GameState *gs);
void model_encontrar_primeiro_jogador(GameState *gs);
int model_jogar_peca(GameState *gs, int indice_peca_usuario, char lado);
int model_comprar_peca(GameState *gs);
int model_pode_passar(const GameState *gs);
void model_trocar_jogador(GameState *gs);
void model_checar_fim_de_jogo(GameState *gs);
int model_contar_pecas_jogador(const GameState *gs, int jogador);
int model_jogador_pode_jogar(const GameState *gs);

#endif