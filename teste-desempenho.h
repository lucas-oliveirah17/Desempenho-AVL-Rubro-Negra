// arquivo teste-desempenho.h

#ifndef TESTE_DESEMPENHO_H
#define TESTE_DESEMPENHO_H

#include "arvoreAVL.h"

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
    RUBRO,
}Arvore;

int call_menu_AVL();
int call_menu_RN();
int wrapper_AVL_desordenado();
int wrapper_AVL_ordenado();
int wrapper_AVL_ambos();

StatusOP testar_arvore(const char* nome_arquivo, Arvore arvore);
StatusOP inserir_arvore(Arvore arvore, void *estrutura, Funcionario funcionario);
StatusOP liberar_arvore(Arvore arvore, void *estrutura);
StatusOP salvar_dados(Arvore arvore, void *estrutura, char* header, int quantidade);

StatusOP arquivo_nao_existe(const char* nome_arquivo);
Funcionario carregar_funcionario(char *linha);
void print_funcionario(Funcionario func);

void countingSort(int *inputArray, int numElementos);

#endif // TESTE_DESEMPENHO_H_INCLUDED
