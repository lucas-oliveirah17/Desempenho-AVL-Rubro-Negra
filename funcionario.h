// Arquivo funcionario.h

#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct Funcionario {
    int codigo;
    char* nome;
    int idade;
    char* empresa;
    char* departamento;
    float salario;
} Funcionario;

#endif // FUNCIONARIO_H
