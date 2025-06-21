// arquivo teste-desempenho.h

#ifndef TESTE_DESEMPENHO_H
#define TESTE_DESEMPENHO_H

#include "arvoreAVL.h"

#define ARQUIVO_DESORDENADO "massaDados.csv"
#define ARQUIVO_ORDENADO "massaDadosOrdenado.csv"

typedef enum{
    ARQUIVO_NAO_ENCONTRADO = 1,
    ARQUIVO_ENCONTRADO = 0,

    OPERACAO_CONCLUIDA = 0
}StatusOP;

int call_menu_AVL();
int call_menu_RN();
int wrapper_AVL_desordenado();

void print_funcionario(Funcionario func);
Funcionario carregar_funcionario(char *linha);

StatusOP arquivo_nao_existe(const char* nome_arquivo);
StatusOP teste_arvore_AVL(const char* nome_arquivo);
StatusOP salvar_dados(arvAVL *dados, char* header, int quantidade);

void countingSort(int *inputArray, int numElementos);

#endif // TESTE_DESEMPENHO_H_INCLUDED
