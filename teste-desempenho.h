#ifndef TESTE_DESEMPENHO_H
#define TESTE_DESEMPENHO_H

typedef struct Funcionario{
    int codigo;
    char* nome;
    int idade;
    char* empresa;
    char* departamento;
    float salario;
}Funcionario;

typedef enum{
    ARQUIVO_NAO_ENCONTRADO = 1,
    ARQUIVO_ENCONTRADO = 0
}StatusOP;

int call_menu_AVL();
int call_menu_RN();

void print_funcionario(Funcionario func);
StatusOP arquivo_nao_existe(char* nome_arquivo);

#endif // TESTE_DESEMPENHO_H_INCLUDED
