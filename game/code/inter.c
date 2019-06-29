// Inclusão de pacotes (headers):

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <menu.h>
#include <inter.h>
#include <trans.h>
#include <kbhit.h>

// Declarando ao arquivo as estruturas de dados globais (struct):

extern gl_exclv exclv;
extern gl_level level;
extern gl_score score;
extern gl_check check;

// Declaração de variáveis globais ao programa:

int op;

// Funções intermediárias:

// Checando a dificuldade e atribuindo à check dados do jogo
void mode_checker(){ 
    if(level.dif==OP_NOR){
        check.lev=level.nor;
        check.sall=score.nall;
        check.slk=score.nlk;
    }
    else if(level.dif==OP_INS){
        check.lev=level.ins;
        check.sall=score.iall;
        check.slk=score.ilk;
    }
}

// Devolve os valores agora modificados às estruturas originais
void mode_assigner(){ 
    if(level.dif==OP_NOR){
        level.nor=check.lev;
        score.nall=check.sall;
        score.nlk=check.slk;
    }
    else if(level.dif==OP_INS){
        level.ins=check.lev;
        score.iall=check.sall;
        score.ilk=check.slk;
    }
}

// Função base para execução do jogo
void lev_analyze () {
    while(state==ST_UPD){
        mode_checker();
        lev_variables();
        scor_increase();
        scor_goal();
        lev_option();
        printf("Caracter digitado: %c\n\r", op);
    }
    st_machine();
}

// Aqui posteriormente serão passadas as funções da bolinha, barra...
void lev_variables () {
    printf("Display do nível %d!\n\r", check.lev);
}

// Você vai teclar alguma coisa?
void lev_option () {
    lin_kbhit();
    usleep(SCENE_TIME);
    system("clear");
    switch (op){
        case OP_MENU: // ascii 109
            state=ST_MENU;
            break;
        case OP_QUIT: // ascii 113
            state=ST_QUIT;
            break;
    }
}
    
void scor_increase(){
    (score.lev)++;
}

// Passou de nível ou ganhou o jogo?    
void scor_goal(){
    if(score.lev==SCORE_GOAL){
        system("clear");
        scor_operation();
        if(check.lev==LEVEL_3){
            check.slk=1;
            eg_display();
            mode_assigner();
            exclv.emnu=1;
            ex_verify();
        }
        else{
            (check.lev)++; // LEVEL_1 --> LEVEL_2 --> LEVEL_3
            el_display();
            mode_assigner();
            exclv.enxt=1;
            ex_verify();
        }
    }
}

// Acumulador de pontuação
void scor_operation () {
    if(check.slk==0){
        check.sall=check.sall+score.lev;
    }
    score.lev=0;
}

void el_display () {
    for(i=0; i<50; i++) {
        if((i>=0 && i<8) || (i>=9 && i<16) || (i>=17 && i<25) || (i>=26 && i<33) || (i>=34 && i<42) || (i>=43 && i<50)) {
            for(j=0;j<50;j++){
                printf("[]");
            }
            printf("\n\r");
        }
        else if(i==8){
            printf("[][][][][][][][][][][][][][][][][][]  W A L L    B R E A K E R  [][][][][][][][][][][][][][][][][][]\n\r");
        }
        else if(i==16){
            printf("[][][][][][][][][][][][][][][][][][][]  P A R A B É N S ! ! ! [][][][][][][][][][][][][][][][][][][]\n\r");
        }
        else if(i==25){
            printf("[][][][][][][][][][][][][][][]  P O N T U A Ç Ã O   A T U A L :  %d  [][][][][][][][][][][][][][][]\n\r", check.sall);
        }
        else if(i==33){
            printf("[][][][][][][][][][][][][][][]    ( X )   P R Ó X I M A    F A S E    [][][][][][][][][][][][][][][]\n\r");
        }
        else if(i==42){
            printf("[][][][][][][][][][][][][][][][][][]    J O G O    S A L V O    [][][][][][][][][][][][][][][][][][]\n\r");
        }
    }
}

void eg_display () {
    for(i=0; i<50; i++) {
        if((i>=0 && i<8) || (i>=9 && i<16) || (i>=17 && i<25) || (i>=26 && i<33) || (i>=34 && i<42) || (i>=43 && i<50)) {
            for(j=0;j<50;j++){
                printf("[]");
            }
            printf("\n\r");
        }
        else if(i==8){
            printf("[][][][][][][][][][][][][][][][][][]  W A L L    B R E A K E R  [][][][][][][][][][][][][][][][][][]\n\r");
        }
        else if(i==16){
            printf("[][][][][][][][][][][][][][][][][][][]  P A R A B É N S ! ! ! [][][][][][][][][][][][][][][][][][][]\n\r");
        }
        else if(i==25){
            printf("[][][][][][][][][][][][][][][]  P O N T U A Ç Ã O   F I N A L :  %d  [][][][][][][][][][][][][][][]\n\r", check.sall);
        }
        else if(i==33){
            printf("[][][][][][][][][][][][][][]   ( M )    V O L T A R    A O    M E N U   [][][][][][][][][][][][][][]\n\r");   
        }
        else if(i==42){
            printf("[][][][][][][][][][][][][][][][][][]    J O G O    S A L V O    [][][][][][][][][][][][][][][][][][]\n\r");
        }
    }
}
