// Arquivo main.c

#include <stdio.h>
#include <stdlib.h>

#include "dynamic-menu.h"
#include "colors-menu.h"
#include "teste-desempenho.h"
#include "arvoreAVL.h"
#include "arvoreLLRB.h"

int main()
{
    ItemMenu itemMainMenu[] = {
        {.label = "Arvore AVL", .action = call_menu_AVL},
        {.label = "Arvore Rubro-Negra", .action = call_menu_RN},
        {.label = "SAIR", .action = exit_menu}
    };
    int columnsMenu = 1;
    int gapMenu = 2;

    Menu mainMenu = CREATE_MENU(
        "DESEMPENHO AVL x RUBRO-NEGRA",
        itemMainMenu,
        columnsMenu,
        gapMenu
    );

    run_menu(&mainMenu);
    return 0;
}
