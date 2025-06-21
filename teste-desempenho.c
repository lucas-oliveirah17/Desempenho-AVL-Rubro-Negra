// arquivo teste-desempenho.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "dynamic-menu.h"
#include "colors-menu.h"
#include "teste-desempenho.h"
#include "funcionario.h"

// Funções para teste
int functionTest1(){printf("Option 1 selected.\n"); system("PAUSE"); return 0;}
int functionTest2(){printf("Option 2 selected.\n"); system("PAUSE"); return 0;}

int call_menu_AVL(){
    Menu menu;
    ItemMenu itemMenu[] = {
        {.label = "Teste Desordenado", .action = wrapper_AVL_desordenado},
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

    if(arquivo_nao_existe(ARQUIVO_ORDENADO)){
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

    if(arquivo_nao_existe(ARQUIVO_ORDENADO)){
        disable_item(&menu, "Teste Ordenado");
    }

    run_menu(&menu);
    return 0;
}

int wrapper_AVL_desordenado(){
    teste_arvore_AVL(ARQUIVO_DESORDENADO);
    return 0;
}

void print_funcionario(Funcionario func){
    printf(TEXT_COLOR "\n------------------------------");
    printf("\nCodigo: %d", func.codigo);
    printf("\nNome: %s", func.nome);
    printf("\nIdade: %d", func.idade);
    printf("\nEmpresa: %s", func.empresa);
    printf("\nDepartamento: %s", func.departamento);
    printf("\nSalario: R$ %.2f", func.salario);
    printf("\n------------------------------\n");
    system("PAUSE");
    printf(COLOR_RESET);
}

StatusOP arquivo_nao_existe(const char* nome_arquivo){
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

StatusOP teste_arvore_AVL(const char* nome_arquivo){
    FILE *arquivo;
    Funcionario funcionario;
    int numeroFuncionario = 0;

    arvAVL *arvoreAVL;
    arvoreAVL = cria_arvAVL();

    struct timeval tempoInicio, tempoFim;
    double tempoMedido;

    gettimeofday(&tempoInicio, NULL);

    arquivo = (fopen(nome_arquivo, "r"));
    if(arquivo == NULL){
        return ARQUIVO_NAO_ENCONTRADO;
    }

    char dados[256];
    char headerDados[256];

    fgets(headerDados, sizeof(dados), arquivo);

    while(fgets(dados, sizeof(dados), arquivo)){
        funcionario = carregar_funcionario(dados);
        numeroFuncionario++;
        insere_arvAVL(arvoreAVL, funcionario);
    }

    gettimeofday(&tempoFim, NULL);
    tempoMedido = (tempoFim.tv_sec + tempoFim.tv_usec/1000000.0) -
            (tempoInicio.tv_sec + tempoInicio.tv_usec/1000000.0);

    printf(TEXT_COLOR "\nTempo decorrido: %lfs", tempoMedido);
    printf("\nFoi adicionado %d elementos na arvore\n", numeroFuncionario);
    system("PAUSE");
    printf(COLOR_RESET);

    if(arquivo_nao_existe(ARQUIVO_ORDENADO)){
        salvar_dados(arvoreAVL, headerDados, numeroFuncionario);
        printf(TEXT_COLOR "\nArquivo ordenado gerado!\n");
        system("PAUSE");
        printf(COLOR_RESET);
    }

    fclose(arquivo);
    liberar_arvAVL(arvoreAVL);

    return OPERACAO_CONCLUIDA;
}

Funcionario carregar_funcionario(char *linha){
    Funcionario funcionario;

    funcionario.codigo = atoi(strtok(linha, ";"));
    strcpy(funcionario.nome, strtok(NULL, ";"));
    funcionario.idade = atoi(strtok(NULL, ";"));
    strcpy(funcionario.empresa, strtok(NULL, ";"));
    strcpy(funcionario.departamento, strtok(NULL, ";"));
    funcionario.salario = atof(strtok(NULL, "\n"));

    return funcionario;
}

StatusOP salvar_dados(arvAVL *dados, char* header, int quantidade){
    FILE *arquivo;
    arquivo = (fopen(ARQUIVO_ORDENADO, "w"));

    fprintf(arquivo, "%s", header);

    arvoreToCSV(dados, arquivo);

    return OPERACAO_CONCLUIDA;
}

void countingSort(int *inputArray, int numElementos) {
    int maiorNumero = 0;
    for (int i = 0; i < numElementos; i++){
        if (inputArray[i] > maiorNumero){
            maiorNumero = inputArray[i];
        }
    }

    int* auxArray = (int*)calloc(maiorNumero + 1, sizeof(int));

    for (int i = 0; i < numElementos; i++){
        auxArray[inputArray[i]]++;
    }

    for (int i = 1; i <= maiorNumero; i++){
        auxArray[i] += auxArray[i - 1];
    }

    int* arrayOrdenado = (int*)malloc(numElementos * sizeof(int));
    for (int i = numElementos - 1; i >= 0; i--){
        arrayOrdenado[auxArray[inputArray[i]] - 1] = inputArray[i];
        auxArray[inputArray[i]]--;
    }

    for (int i = 0; i < numElementos; i++){
        inputArray[i] = arrayOrdenado[i];
    }

    free(auxArray);
    free(arrayOrdenado);
}

