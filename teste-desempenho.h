#ifndef TESTE_DESEMPENHO_H
#define TESTE_DESEMPENHO_H

#define ARQUIVO_DESORDENADO "massaDados.csv"
#define ARQUIVO_ORDENADO "massaDadosOrdenado.csv"

typedef struct Funcionario{
    int codigo;
    char nome[100];
    int idade;
    char empresa[100];
    char departamento[50];
    float salario;
}Funcionario;

typedef enum{
    ARQUIVO_NAO_ENCONTRADO = 1,
    ARQUIVO_ENCONTRADO = 0,

    OPERACAO_CONCLUIDA = 0
}StatusOP;

int call_menu_AVL();
int call_menu_RN();

void print_funcionario(Funcionario func);

StatusOP arquivo_nao_existe(char* nome_arquivo);
StatusOP teste_arvore_AVL(char* nome_arquivo);


#endif // TESTE_DESEMPENHO_H_INCLUDED
