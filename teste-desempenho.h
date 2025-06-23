// Arquivo teste-desempenho.h

#ifndef TESTE_DESEMPENHO_H
#define TESTE_DESEMPENHO_H

#include "arvoreAVL.h"
#include "arvoreLLRB.h"

#define ARQUIVO_DESORDENADO "massaDados.csv"
#define ARQUIVO_ORDENADO "massaDadosOrdenado.csv"

typedef enum{
    ARQUIVO_NAO_ENCONTRADO = 1,
    ARQUIVO_ENCONTRADO = 0,

    OPERACAO_CONCLUIDA = 0,
    OPERACAO_FALHOU = 1
}StatusOP;

typedef enum{
    AVL,
    LLRB,
}Arvore;

int call_menu_AVL();
int call_menu_RN();
int wrapper_AVL_desordenado();
int wrapper_AVL_ordenado();
int wrapper_AVL_ambos();
int wrapper_LLRB_desordenado();
int wrapper_LLRB_ordenado();
int wrapper_LLRB_ambos();
int wrapper_testar_todas();

StatusOP testar_arvore(const char* nome_arquivo, Arvore arvore);
StatusOP inserir_arvore(Arvore arvore, void *estrutura, Funcionario funcionario);
StatusOP liberar_arvore(Arvore arvore, void *estrutura);
StatusOP salvar_dados(Arvore arvore, void *estrutura, char* header, int quantidade);

StatusOP arquivo_nao_existe(const char* nome_arquivo);
Funcionario carregar_funcionario(char *linha);
void liberar_funcionario(Funcionario funcionario);
void print_funcionario(Funcionario func);

void countingSort(Funcionario *funcionario, int numElementos);

StatusOP vetorToCSV();

StatusOP vetor_salvar_dados(Funcionario *vetor, char* header, int quantidade);

#endif // TESTE_DESEMPENHO_H_INCLUDED
