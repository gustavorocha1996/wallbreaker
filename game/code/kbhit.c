// Inclusão de pacotes (headers):

#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <fcntl.h>
#include <inter.h>
#include <kbhit.h>
#include <unistd.h>

// Função inspirada no Windows:

void lin_kbhit() {
    struct termios oldt, newt;
    int oldf;
 
    // Na kbhit, tanto faz se o usuário teclar ou não:
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
    op = tolower(getchar());
  
    // O cenário vai ser atualizado de qualquer forma: 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(op==EOF){
        op=63; // Caracter ?
    } 
}
