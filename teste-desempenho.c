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
        {.label = "Teste Ordenado", .action = wrapper_AVL_ordenado},
        {.label = "Testar Ambos", .action = wrapper_AVL_ambos},

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
        {.label = "Teste Ambos", .action = functionTest1},

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
    testar_arvore(ARQUIVO_DESORDENADO, AVL);
    return 0;
}

int wrapper_AVL_ordenado(){
    testar_arvore(ARQUIVO_ORDENADO, AVL);
    return 0;
}

int wrapper_AVL_ambos(){
    printf(TEXT_COLOR2 "\nTESTE DESORDENADO:\n");
    testar_arvore(ARQUIVO_DESORDENADO, AVL);

    printf(TEXT_COLOR2"\nTESTE ORDENADO:\n"COLOR_RESET);
    testar_arvore(ARQUIVO_ORDENADO, AVL);
    return 0;
}

StatusOP testar_arvore(const char* nome_arquivo, Arvore arvore){
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(!arquivo) return ARQUIVO_NAO_ENCONTRADO;

    char linha[256];
    char header[256];
    int numeroFuncionario = 0;
    Funcionario funcionario;

    struct timeval tempoInicio, tempoFim;
    double tempoMedido;

    void* estrutura = NULL;
    if(arvore == AVL) estrutura = (void*) cria_arvAVL();

    fgets(header, sizeof(header), arquivo);

    gettimeofday(&tempoInicio, NULL);
    while (fgets(linha, sizeof(linha), arquivo)) {
        funcionario = carregar_funcionario(linha);
        inserir_arvore(arvore, estrutura, funcionario);
        numeroFuncionario++;
    }

    gettimeofday(&tempoFim, NULL);

    fclose(arquivo);

    tempoMedido = (tempoFim.tv_sec + tempoFim.tv_usec/1000000.0) -
            (tempoInicio.tv_sec + tempoInicio.tv_usec/1000000.0);

    printf(TEXT_COLOR "\nTempo decorrido: %lfs", tempoMedido);
    printf("\nFoi adicionado %d elementos na arvore\n", numeroFuncionario);
    system("PAUSE");
    printf(COLOR_RESET);

    liberar_arvore(arvore, estrutura);

    if(arquivo_nao_existe(ARQUIVO_ORDENADO)){
        salvar_dados(arvore, estrutura, header, numeroFuncionario);
        printf(TEXT_COLOR "\nArquivo ordenado gerado!\n");
        system("PAUSE");
        printf(COLOR_RESET);
    }

    return OPERACAO_CONCLUIDA;
}

StatusOP inserir_arvore(Arvore arvore, void *estrutura, Funcionario funcionario){
    if(arvore == AVL){
        return insere_arvAVL(estrutura, funcionario);
    }

    return OPERACAO_FALHOU;
}

StatusOP liberar_arvore(Arvore arvore, void *estrutura){
    if(arvore == AVL){
        liberar_arvAVL(estrutura);
        return OPERACAO_CONCLUIDA;
    }

    return OPERACAO_FALHOU;
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

StatusOP salvar_dados(Arvore arvore, void *estrutura, char* header, int quantidade){
    FILE *arquivo;
    arquivo = (fopen(ARQUIVO_ORDENADO, "w"));

    fprintf(arquivo, "%s", header);

    if(arvore == AVL){
        arvoreToCSV(estrutura, arquivo);
    }
    else return OPERACAO_FALHOU;

    fclose(arquivo);
    return OPERACAO_CONCLUIDA;
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
