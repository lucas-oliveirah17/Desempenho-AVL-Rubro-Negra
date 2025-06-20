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

int call_menu_AVL();
int call_menu_RN();

void print_funcionario(Funcionario func);

#endif // TESTE_DESEMPENHO_H_INCLUDED
