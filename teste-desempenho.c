#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic-menu.h"
#include "colors-menu.h"
#include "teste-desempenho.h"

// Funções para teste
int functionTest1(){printf("Option 1 selected.\n"); system("PAUSE"); return 0;}
int functionTest2(){printf("Option 2 selected.\n"); system("PAUSE"); return 0;}

int call_menu_AVL(){
    Menu menu;
    ItemMenu itemMenu[] = {
        {.label = "Teste Desordenado", .action = functionTest1},
        {.label = "Teste Ordenado", .action = functionTest2},

        {.label = "VOLTAR", .action = exit_menu}
    };

    int columnsMenu = 1;
    int gapMenu = 2;

    menu = CREATE_MENU(
        "ARVORE AVL",
        itemMenu,
        columnsMenu,
        gapMenu
    );

    run_menu(&menu);
    return 0;
}

int call_menu_RN(){
    Menu menu;
    ItemMenu itemMenu[] = {
        {.label = "Teste Desordenado", .action = functionTest1},
        {.label = "Teste Ordenado", .action = functionTest2},

        {.label = "VOLTAR", .action = exit_menu}
    };

    int columnsMenu = 1;
    int gapMenu = 2;

    menu = CREATE_MENU(
        "ARVORE RUBRO-NEGRA",
        itemMenu,
        columnsMenu,
        gapMenu
    );

    run_menu(&menu);
    return 0;
}

