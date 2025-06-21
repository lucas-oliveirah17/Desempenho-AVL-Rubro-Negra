// Arquivo funcionario.h

#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct Funcionario {
    int codigo;
    char nome[100];
    int idade;
    char empresa[100];
    char departamento[50];
    float salario;
} Funcionario;

#endif // FUNCIONARIO_H
