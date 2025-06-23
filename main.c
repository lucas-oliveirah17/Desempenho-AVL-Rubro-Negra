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
    if(arquivo_nao_existe(ARQUIVO_ORDENADO)){
        vetorToCSV();
    }

    ItemMenu itemMainMenu[] = {
        {.label = "Arvore AVL", .action = call_menu_AVL},
        {.label = "Arvore Rubro-Negra", .action = call_menu_RN},
        {.label = "Testar todas", .action = wrapper_testar_todas},

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

    if(arquivo_nao_existe(ARQUIVO_DESORDENADO)){
        disable_item(&mainMenu, "Testar todas");
    }

    run_menu(&mainMenu);
    return 0;
}
