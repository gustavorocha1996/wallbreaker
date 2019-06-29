// Inclusão de pacotes (headers):

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ctype.h>
#include <menu.h>
#include <inter.h>
#include <trans.h>
#include <bonus.h>

// Declarando ao arquivo as estruturas de dados globais (struct):

extern gl_exclv exclv;
extern gl_level level;
extern gl_score score;

// Definindo constantes (diretivas de pré-processamento):

#define OP_DIF 115 // Letra S
#define OP_CRED 99 // Letra C
#define OP_RES 114 // Letra R
#define OP_NEXT 120 // Letra X

// Declaração de variáveis globais ao programa:

int res=0;

// Funções de transição:

// Verificando o que o usuário vai teclar até que seja uma das teclas definidas
// O estado (state) é passado para st_machine
void ex_verify(){
    while(exclv.test!=1){
        op=tolower(getchar());
        if(op==OP_MENU && exclv.emnu==1){
            res=0;
            state=ST_MENU;
            exclv.test=1;
        }
        else if(op==OP_DIF && exclv.edif==1){
            state=ST_DIF;
            exclv.test=1;
        }
        else if(op==OP_CRED && exclv.ecrd==1){
            state=ST_CRED;
            exclv.test=1;
        }
        else if(op==OP_RES && exclv.eres==1){
            res=1;
            state=ST_RES;
            exclv.test=1;
        }
        else if(op==OP_QUIT && exclv.eqit==1){
            state=ST_QUIT;
            exclv.test=1;
        }
        else if((op==OP_NOR || op==OP_INS) && exclv.eni==1){
            level.dif=op;
            state=ST_UPD;
            exclv.test=1;
        }
        else if(op==OP_NEXT && exclv.enxt==1){
            exclv.test=1;
        }
    }
    ex_false();
    st_machine();
}

// Após verificar, zeramos tudo!
void ex_false(){
    exclv.test=0;
    exclv.emnu=0;
    exclv.edif=0;
    exclv.ecrd=0;
    exclv.eres=0;
    exclv.eqit=0;
    exclv.eni=0;
    exclv.enxt=0;
}

// Chama funções display (de acordo com o state) para atualizar a cena
void st_machine(){
    system("clear");
    switch (state) {
        case ST_MENU:
            score.lev=0;
            ee_verify();
            if(res==1){
                res_display();
            }
            else{
                menu_display();
            }
            break;
        case ST_DIF:
            dif_display();
            break;
        case ST_CRED:
            cred_display();
            break;
        case ST_RES:
            res_progress();
            break;
        case ST_QUIT:
            endwin();
            exit(0);
            break;
        case ST_UPD:
            printf("Caracter digitado: ?\n\r");
            lev_analyze();
            break;
    }
}
