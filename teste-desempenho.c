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

    if(arquivo_nao_existe("massaDadosOrdenado.csv")){
        disable_item(&menu, "Teste Ordenado");
    }

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

    if(arquivo_nao_existe("massaDadosOrdenado.csv")){
        disable_item(&menu, "Teste Ordenado");
    }

    run_menu(&menu);
    return 0;
}

void print_funcionario(Funcionario func){
    printf("\n------------------------------");
    printf("\nCodigo: %d", func.codigo);
    printf("\nNome: %s", func.nome);
    printf("\nIdade: %d", func.idade);
    printf("\nEmpresa: %s", func.empresa);
    printf("\nDepartamento: %s", func.departamento);
    printf("\nSalario: R$ %.2f", func.salario);
    printf("\n------------------------------\n");
}

StatusOP arquivo_nao_existe(char* nome_arquivo){
    FILE *arquivo;
    arquivo = (fopen(nome_arquivo, "r"));
    if(arquivo == NULL){
        return ARQUIVO_NAO_ENCONTRADO;
    }
    else {
        fclose(arquivo);
        return ARQUIVO_ENCONTRADO;
    }
}
