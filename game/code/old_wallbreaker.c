// Comando para compilação: f=old_wallbreaker; gcc -o $f $f.c -lncurses -Wall; ./$f; rm $f

// Inclusão de pacotes (headers):

#include <stdio.h>
#include <stdlib.h> // system, dentre outras
#include <curses.h> // teclar s/ dar enter
#include <ctype.h> // tolower
#include <unistd.h> // sleep e usleep
#include <termios.h> // kbhit
#include <fcntl.h> // kbhit
// #include <math.h>
// #include <string.h>

// Definindo constantes (diretivas de pré-processamento):

#define OP_MENU 109 // Letra M
#define OP_DIF 115 // Letra S
#define OP_CRED 99 // Letra C
#define OP_RES 114 // Letra R
#define OP_QUIT 113 // Letra Q
#define OP_NOR 110 // Letra N
#define OP_INS 105 // Letra I
#define OP_NEXT 120 // Letra X
#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define SCENE_TIME 50000 // 0,05s
#define PAUSE_TIME 5 // 5s
#define SCORE_GOAL 200 // Como à cada 1s, temos 20 atualizações... em 10s, serão 200!

// Declaração da máquina de estados:

/* Aqui, só foram passados os estados que: 
1º) Deve-se teclar, aparecendo imediatamente um display.
Ex: ST_WIN não existe, pois o display aparece sem teclar. 
2º) Devem ser usados várias vezes no programa. Caso contrário, aumenta custo computacional.
Ex: ST_DOGE não existe, pois o display só aparece uma única vez antes de resetar. */
enum {ST_MENU=1, ST_DIF, ST_CRED, ST_RES, ST_QUIT, ST_UPD} state; 

// Declaração de variáveis como estruturas de dados (struct):

struct {bool test; bool emnu; bool edif; bool ecrd; bool eres; bool eqit; bool eni; bool enxt; } exclv = {0, 0, 0, 0, 0, 0, 0, 0};
struct { int dif ; int nor; int ins; } level = {EOF, LEVEL_1, LEVEL_1};
struct { int lev ; int nall; bool nlk; int iall; bool ilk; } score = {0, 0, 0, 0, 0}; 
struct { int lev; int sall; int slk; } check = {EOF, EOF, EOF};

// Declaração de variáveis globais ao programa:

int op, i, j; 
bool res=0, ee=0;

// Protótipos de funções do menu:

void menu_display ();
void dif_display ();
void cred_display ();
void res_progress();
void res_display();

// Protótipos de funções intermediárias:

void mode_checker();
void mode_assigner();
void lev_analyze();
void lev_variables();
void lev_option();
void scor_increase();
void scor_goal();
void scor_operation();
void el_display();
void eg_display();

// Protótipos das funções de transição:

void ex_verify();
void ex_false();
void st_machine();

// Protótipo de função inspirada no Windows:

void lin_kbhit();

// Protótipos de funções Easter Egg:

void ee_verify();
void ee_display();

/* Protótipos de funções para as variáveis:

(...) */

/* Protótipos de funções para as interações:

(...) */

// Função principal:

int main (void) {
    initscr();
    system("clear");
    menu_display();
    return 0;
}

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
    exclv.emnu=1;
    ex_verify();
}

void res_progress () {
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
    exclv.edif=1;
    exclv.ecrd=1;
    exclv.eres=1;
    exclv.eqit=1;
    ex_verify();
}

// Funções intermediárias:

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

void lev_variables () {
    printf("Display do nível %d!\n\r", check.lev);
}

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

// Funções de transição:

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


// Função inspirada no Windows:

void lin_kbhit() {
    struct termios oldt, newt;
    int oldf;
 
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
    op = tolower(getchar());
 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(op==EOF){
        op=63; // Caracter ?
    } 
}

// Funções Easter Egg:

void ee_verify () {
    if(score.nlk==1 && score.ilk==1 && ee==0){
        ee=1;
        ee_display();
        sleep(PAUSE_TIME);
        system("clear");
    }
}

void ee_display () {
    for(i=0; i<50; i++) {
        if((i>=0 && i<10) || (i>=31 && i<39) || (i>=40 && i<50)) {
            for(j=0;j<50;j++){
                printf("[]");
            }
            printf("\n\r");
        }
        else if(i==11){
            printf("[][][][][][][][][][][][][][][][]░░░░░░░░░░░▄░░░░░░░░░░░░░░▄░░░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░░░░░░░▌▒█░░░░░░░░░░░▄▀▒▌░░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░░░░░░░▌▒▒█░░░░░░░░▄▀▒▒▒▐░░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░░░░░░▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐░░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░░░░▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐░░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░░▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌░░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░▀▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒▐░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▒▌░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▐░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▒▌░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒▐░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░▀▄▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▄▒▒▒▒▌░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░░░▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀░░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░░░░░▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀░░░░░░[][][][][][][][][][][][][][][][][][]\n\r");
            printf("[][][][][][][][][][][][][][][][]░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▀▀░░░░░░░░░[][][][][][][][][][][][][][][][][][]\n\r");
            i=30;
        }
        else if(i==39){
            printf("[][][][][][][][][][][][][]   V O C Ê   Z E R O U   O   J O G O  !  !  !   [][][][][][][][][][][][][]\n\r");
        }
    }
}
