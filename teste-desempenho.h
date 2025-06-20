#ifndef TESTE_DESEMPENHO_H
#define TESTE_DESEMPENHO_H

typedef struct{
    int codigo;
    char* nome;
    int idade;
    char* empresa;
    char* departamento;
    float salario;
}Funcionario;


int call_menu_AVL();
int call_menu_RN();

#endif // TESTE_DESEMPENHO_H_INCLUDED
