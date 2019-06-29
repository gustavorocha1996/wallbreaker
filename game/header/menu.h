#ifndef MENU
#define MENU

// Definindo constantes (diretivas de pré-processamento):

#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3

// Declaração de variáveis como estruturas de dados em um tipo anônimo (struct):

typedef struct { int test; int emnu; int edif; int ecrd; int eres; int eqit; int eni; int enxt; } gl_exclv;
typedef struct { int dif ; int nor; int ins; } gl_level;
typedef struct { int lev ; int nall; int nlk; int iall; int ilk; } gl_score;

// Declaração de variáveis globais ao programa:

extern int i, j;

// Protótipos de funções do menu:

extern void menu_display(); // Display do menu
extern void dif_display(); // Display da dificuldade
extern void cred_display(); // Display dos créditos
extern void res_progress(); // Reseta o jogo
extern void res_display(); // Display do menu c/ reset

#endif
