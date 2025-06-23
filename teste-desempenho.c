// Arquivo teste-desempenho.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "dynamic-menu.h"
#include "colors-menu.h"
#include "teste-desempenho.h"
#include "funcionario.h"

int call_menu_AVL(){
    Menu menu;
    ItemMenu itemMenu[] = {
        {.label = "Testar Desordenado", .action = wrapper_AVL_desordenado},
        {.label = "Testar Ordenado", .action = wrapper_AVL_ordenado},
        {.label = "Testar ambos", .action = wrapper_AVL_ambos},

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

    if(arquivo_nao_existe(ARQUIVO_DESORDENADO)){
        disable_item(&menu, "Testar Desordenado");
    }

    if(arquivo_nao_existe(ARQUIVO_ORDENADO)){
        disable_item(&menu, "Testar Ordenado");
    }

    if(arquivo_nao_existe(ARQUIVO_DESORDENADO)){
        disable_item(&menu, "Testar ambos");
    }

    run_menu(&menu);
    return 0;
}

int call_menu_RN(){
    Menu menu;
    ItemMenu itemMenu[] = {
        {.label = "Testar Desordenado", .action = wrapper_LLRB_desordenado},
        {.label = "Testar Ordenado", .action = wrapper_LLRB_desordenado},
        {.label = "Testar ambos", .action = wrapper_LLRB_ambos},

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

    if(arquivo_nao_existe(ARQUIVO_DESORDENADO)){
        disable_item(&menu, "Testar Desordenado");
    }

    if(arquivo_nao_existe(ARQUIVO_ORDENADO)){
        disable_item(&menu, "Testar Ordenado");
    }

    if(arquivo_nao_existe(ARQUIVO_DESORDENADO)){
        disable_item(&menu, "Testar ambos");
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
    printf(TEXT_COLOR2 "\n    TESTE DESORDENADO:\n");
    testar_arvore(ARQUIVO_DESORDENADO, AVL);

    printf(TEXT_COLOR2 "\n    TESTE ORDENADO:\n" COLOR_RESET);
    testar_arvore(ARQUIVO_ORDENADO, AVL);
    return 0;
}

int wrapper_LLRB_desordenado(){
    testar_arvore(ARQUIVO_DESORDENADO, LLRB);
    return 0;
}

int wrapper_LLRB_ordenado(){
    testar_arvore(ARQUIVO_ORDENADO, LLRB);
    return 0;
}

int wrapper_LLRB_ambos(){
    printf(TEXT_COLOR2 "\n    TESTE DESORDENADO:\n");
    testar_arvore(ARQUIVO_DESORDENADO, LLRB);

    printf(TEXT_COLOR2 "\n    TESTE ORDENADO:\n" COLOR_RESET);
    testar_arvore(ARQUIVO_ORDENADO, LLRB);
    return 0;
}

int wrapper_testar_todas(){
    printf(TEXT_COLOR2 "\n       ARVORE AVL");
    printf("\n    TESTE DESORDENADO:\n");
    testar_arvore(ARQUIVO_DESORDENADO, AVL);

    printf(TEXT_COLOR2 "\n    TESTE ORDENADO:\n" COLOR_RESET);
    testar_arvore(ARQUIVO_ORDENADO, AVL);

    printf(TEXT_COLOR2 "\n   ARVORE RUBRO-NEGRA");
    printf("\n    TESTE DESORDENADO:\n");
    testar_arvore(ARQUIVO_DESORDENADO, LLRB);

    printf(TEXT_COLOR2 "\n    TESTE ORDENADO:\n" COLOR_RESET);
    testar_arvore(ARQUIVO_ORDENADO, LLRB);

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
    else if(arvore == LLRB) estrutura = (void*) cria_arvoreLLRB();

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

//    if(arquivo_nao_existe(ARQUIVO_ORDENADO)){
//        salvar_dados(arvore, estrutura, header, numeroFuncionario);
//        printf(TEXT_COLOR "\nArquivo ordenado gerado!\n");
//        system("PAUSE");
//        printf(COLOR_RESET);
//    }

    liberar_arvore(arvore, estrutura);

    return OPERACAO_CONCLUIDA;
}

StatusOP inserir_arvore(Arvore arvore, void *estrutura, Funcionario funcionario){
    if(arvore == AVL)return insere_arvAVL(estrutura, funcionario);
    else if(arvore == LLRB)return insere_arvoreLLRB(estrutura, funcionario);

    return OPERACAO_FALHOU;
}

StatusOP liberar_arvore(Arvore arvore, void *estrutura){
    if(arvore == AVL){
        liberar_arvAVL(estrutura);
        return OPERACAO_CONCLUIDA;
    }

    else if(arvore == LLRB){
        liberar_arvoreLLRB(estrutura);
        return OPERACAO_CONCLUIDA;
    }

    return OPERACAO_FALHOU;
}

Funcionario carregar_funcionario(char *linha){
    Funcionario funcionario;
    char* token;

    funcionario.codigo = atoi(strtok(linha, ";"));

    token = strtok(NULL, ";");
    funcionario.nome = malloc(strlen(token) + 1);
    strcpy(funcionario.nome, token);

    funcionario.idade = atoi(strtok(NULL, ";"));

    token = strtok(NULL, ";");
    funcionario.empresa = malloc(strlen(token) + 1);
    strcpy(funcionario.empresa, token);

    token = strtok(NULL, ";");
    funcionario.departamento = malloc(strlen(token) + 1);
    strcpy(funcionario.departamento, token);

    funcionario.salario = atof(strtok(NULL, "\n"));

    return funcionario;
}

void liberar_funcionario(Funcionario funcionario) {
    free(funcionario.nome);
    free(funcionario.empresa);
    free(funcionario.departamento);
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

    if(arvore == AVL) AVLtoCSV(estrutura, arquivo);
    else if(arvore == LLRB) LLRBtoCSV(estrutura, arquivo);
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

void countingSort(Funcionario *funcionario, int quantidade) {
    int maiorCodigo = funcionario[0].codigo;

    for (int i = 0; i < quantidade; i++){
        if (funcionario[i].codigo > maiorCodigo){
            maiorCodigo = funcionario[i].codigo;
        }
    }

    int* contagem = (int*)calloc(maiorCodigo + 1, sizeof(int));

    for (int i = 0; i < quantidade; i++){
        contagem[funcionario[i].codigo]++;
    }

    for (int i = 1; i <= maiorCodigo; i++){
        contagem[i] += contagem[i - 1];
    }

    Funcionario* ordenado = (Funcionario*)malloc(quantidade * sizeof(Funcionario));

    for (int i = quantidade - 1; i >= 0; i--){
        ordenado[contagem[funcionario[i].codigo] - 1] = funcionario[i];
        contagem[funcionario[i].codigo]--;
    }

    for (int i = 0; i < quantidade; i++){
        funcionario[i] = ordenado[i];
    }

    free(contagem);
    free(ordenado);
}

StatusOP vetorToCSV(){
    Funcionario *vetor = NULL;
    int capacidade = 10000;
    int tamanho = 0;

    char header[256];
    char linha[256];

    enable_color_mode();

    vetor = (Funcionario*) malloc(capacidade * sizeof(Funcionario));
    if(!vetor) return OPERACAO_FALHOU;

    FILE *arquivo = fopen(ARQUIVO_DESORDENADO, "r");

    fgets(header, sizeof(header), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        if(tamanho >= capacidade){
            capacidade *=2;
            vetor = (Funcionario*) realloc(vetor, capacidade * sizeof(Funcionario));
        }

        vetor[tamanho++] = carregar_funcionario(linha);
    }

    //vetor = realloc(vetor, tamanho * sizeof(Funcionario));

    fclose(arquivo);

    countingSort(vetor, tamanho);

    vetor_salvar_dados(vetor, header, tamanho);

    printf(TEXT_COLOR "\nArquivo ordenado com %d elementos criado\n", tamanho);
    system("PAUSE");
    printf(COLOR_RESET);

    return OPERACAO_CONCLUIDA;
}

StatusOP vetor_salvar_dados(Funcionario *vetor, char* header, int quantidade){
    FILE *arquivo;
    arquivo = (fopen(ARQUIVO_ORDENADO, "w"));

    fprintf(arquivo, "%s", header);

    for(int i = 0; i < quantidade; i++){
        fprintf(arquivo, "%d;%s;%d;%s;%s;%.2f\n",
            vetor[i].codigo,
            vetor[i].nome,
            vetor[i].idade,
            vetor[i].empresa,
            vetor[i].departamento,
            vetor[i].salario);
    }

    fclose(arquivo);
    return OPERACAO_CONCLUIDA;
}
