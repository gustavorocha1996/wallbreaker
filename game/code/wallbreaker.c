// Nesse caso, os .c e .h ficam em pastas diferentes. Em seguida, definimos o Makefile.
// Comandos para compilação (o diretório deve estar na pasta Code): make ou make run.

// Inclusão de pacotes (headers):

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <menu.h>

// Função principal:

int main (void) {
    // Alterando o estado do terminal para o uso da curses.h
    initscr(); 
    system("clear");
    menu_display();
    return 0;
}
