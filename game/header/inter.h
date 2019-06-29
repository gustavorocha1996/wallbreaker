#ifndef INTER
#define INTER

// Definindo constantes (diretivas de pré-processamento):

#define OP_MENU 109 // Letra M
#define OP_QUIT 113 // Letra Q
#define OP_NOR 110 // Letra N
#define OP_INS 105 // Letra I
#define SCENE_TIME 50000 // 0,05 s
#define SCORE_GOAL 200 // Como à cada 1s, temos 20 atualizações... em 10s, serão 200!

// Declaração da máquina de estados:

/* Aqui, só foram passados os estados que: 
1º) Deve-se teclar, aparecendo imediatamente um display.
Ex: ST_WIN não existe, pois o display aparece sem teclar. 
2º) Devem ser usados várias vezes no programa. Caso contrário, aumenta custo computacional.
Ex: ST_DOGE não existe, pois o display só aparece uma única vez antes de resetar. */
enum {ST_MENU=1, ST_DIF, ST_CRED, ST_RES, ST_QUIT, ST_UPD} state; 

// Declaração de variáveis como uma estrutura de dados em um tipo anônimo (struct):

typedef struct { int lev; int sall; int slk; } gl_check; 

// Declaração de variáveis globais ao programa:

extern int op;

// Protótipos de funções intermediárias:

extern void mode_checker(); // Checa a dificuldade escolhida
extern void mode_assigner(); // Devolve os dados às structs
extern void lev_analyze(); // Função base do jogo
extern void lev_variables(); // Bloco, barra, bolinha...
extern void lev_option(); // O que vc teclou?
extern void scor_increase(); // Incrementando a pontuação
extern void scor_goal(); // Mudando de fase...
extern void scor_operation(); // Acumula a pontuação
extern void el_display(); // Display fim de fase
extern void eg_display(); // Display fim de jogo

#endif
