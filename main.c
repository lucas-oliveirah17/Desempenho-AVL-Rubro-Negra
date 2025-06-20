#include <stdio.h>
#include <stdlib.h>
#include "dynamic-menu.h"
#include "colors-menu.h"
#include "teste-desempenho.h"

int main()
{
//    Funcionario f;
//    f.codigo = 23;
//    f.nome = "Lucas";
//    f.idade = 22;
//    f.departamento = "TI";
//    f.empresa = "Google";
//    f.salario = 3254.56;
//    print_funcionario(f);
//    system("PAUSE");

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
