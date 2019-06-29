// Inclusão de pacotes (headers):

#include <stdio.h>
#include <menu.h>
#include <trans.h>

// Declarando ao arquivo as estruturas de dados globais (struct):

extern gl_exclv exclv;
extern gl_level level;
extern gl_score score;

// Declaração de variáveis globais ao programa:

int i, j;

// Funções do menu:

void menu_display () {
    for(i=0; i<50; i++) {
        if((i>=0 && i<15) || (i>=16 && i<31) || (i>=35 && i<50)) {
            for(j=0;j<50;j++){
                printf("[]");
            }
            printf("\n\r");
        }
        else if(i==15){
            printf("[][][][][][][][][][][][][][][][][][]  W A L L    B R E A K E R  [][][][][][][][][][][][][][][][][][]\n\r");
        }
        else if(i>=31 && i<35){
            printf("[][][][][][][][][][][][][][][][]  ( S )  C O M E Ç A R    J O G O   [][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]  ( C )       C R É D I T O S       [][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]  ( R )  R E S E T A R    J O G O   [][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]  ( Q )  S A I R    D O    J O G O  [][][][][][][][][][][][][][][][]\n\r");
            i=34;
        }
    }
    // Opções permitidas:
    exclv.edif=1;
    exclv.ecrd=1;
    exclv.eres=1;
    exclv.eqit=1;
    ex_verify();
}

void dif_display () {
    for(i=0; i<50; i++) {
        if((i>=0 && i<16) || (i>=17 && i<24) || (i>=25 && i<32) || (i>=35 && i<50)) {
            for(j=0;j<50;j++){
                printf("[]");
            }
            printf("\n\r");
        }
        else if(i==16){
            printf("[][][][][][][][][][][][][][][][][][]  W A L L    B R E A K E R  [][][][][][][][][][][][][][][][][][]\n\r");
        }
        else if(i==24){
            printf("[][][][][][][][][][][][][]  E S C O L H A    A    D I F I C U L D A D E:  [][][][][][][][][][][][][]\n\r");
        }
        else if(i>=32 && i<35){
            printf("[][][][][][][][][][][][][][]   ( N )       N Í V E L    N O R M A L     [][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][]   ( I )       N Í V E L    I N S A N O     [][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][]   ( M )    V O L T A R    A O    M E N U   [][][][][][][][][][][][][][]\n\r");
            i=34;
        }
    }
    // Opções permitidas:
    exclv.eni=1;
    exclv.emnu=1;
    ex_verify();
}

void cred_display () {
    for(i=0; i<50; i++) {
        if((i>=0 && i<8) || (i>=9 && i<11) || (i>=12 && i<41) || (i>=42 && i<50)) {
            for(j=0;j<50;j++){
                printf("[]");
            }
            printf("\n\r");
        }
        else if(i==8){
            printf("[][][][][][][][][][][][][][][][][][]  W A L L    B R E A K E R  [][][][][][][][][][][][][][][][][][]\n\r");
        }
        else if(i==11){
            printf("[][][][][][][][][][][][][][][][][][][][]  C R É D I T O S:  [][][][][][][][][][][][][][][][][][][][]\n\r");
        }
        else if(i==41){
            printf("[][][][][][][][][][][][][][]   ( M )    V O L T A R    A O    M E N U   [][][][][][][][][][][][][][]\n\r");
        }
    }
    // Opção permitida:
    exclv.emnu=1;
    ex_verify();
}

void res_progress () { // Reseta o progresso do jogo
    level.nor=LEVEL_1;
    level.ins=LEVEL_1;
    score.nall=0;
    score.iall=0;
    score.nlk=0;
    score.ilk=0;
    res_display();
}

void res_display () {
    for(i=0; i<50; i++) {
        if((i>=0 && i<15) || (i>=16 && i<23) || (i>=24 && i<31) || (i>=35 && i<50)) {
            for(j=0;j<50;j++){
                printf("[]");
            }
            printf("\n\r");
        }
        else if(i==15){
            printf("[][][][][][][][][][][][][][][][][][]  W A L L    B R E A K E R  [][][][][][][][][][][][][][][][][][]\n\r");
        }
        else if(i>=31 && i<35){
            printf("[][][][][][][][][][][][][][][][]  ( S )  C O M E Ç A R    J O G O   [][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]  ( C )       C R É D I T O S       [][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]  ( R )  R E S E T A R    J O G O   [][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]  ( Q )  S A I R    D O    J O G O  [][][][][][][][][][][][][][][][]\n\r");
            i=34;
        }
        else if(i==23){
            printf("[][][][][][][][][][][][][][][][][]   J O G O    R E S E T A D O   [][][][][][][][][][][][][][][][][]\n\r");
        }
    }
    // Opções permitidas:
    exclv.edif=1;
    exclv.ecrd=1;
    exclv.eres=1;
    exclv.eqit=1;
    ex_verify();
}
