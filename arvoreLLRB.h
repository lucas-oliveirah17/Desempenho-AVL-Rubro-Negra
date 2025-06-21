// Arquivo arvoreLLRB.h

#ifndef ARVORELLRB_H
#define ARVORELLRB_H

#include "funcionario.h"

typedef struct NO_LLRB *arvoreLLRB;

arvoreLLRB *cria_arvoreLLRB();

void liberar_arvoreLLRB(arvoreLLRB *raiz);

void libera_NO_LLRB(struct NO_LLRB *no);

int vazia_arvoreLLRB(arvoreLLRB *raiz);

int altura_arvoreLLRB(arvoreLLRB *raiz);

int totalNO_arvoreLLRB(arvoreLLRB *raiz);

void preOrdem_arvoreLLRB(arvoreLLRB *raiz);

void emOrdem_arvoreLLRB(arvoreLLRB *raiz);

void posOrdem_arvoreLLRB(arvoreLLRB *raiz);

int consulta_arvoreLLRB(arvoreLLRB*raiz, Funcionario funcionario);

// Código Árvore Rubro Negra

int cor(struct NO_LLRB *H);

void trocaCor(struct NO_LLRB *H);

struct NO_LLRB *rotacionaEsquerda(struct NO_LLRB *A);

struct NO_LLRB *rotacionaDireita(struct NO_LLRB *A);

struct NO_LLRB *move2EsqRED(struct NO_LLRB *H);

struct NO_LLRB *move2DirRED(struct NO_LLRB *H);

struct NO_LLRB *balancear(struct NO_LLRB *H);

int insere_arvoreLLRB(arvoreLLRB *raiz, Funcionario funcionario);

struct NO_LLRB *insereNO(struct NO_LLRB *H, Funcionario funcionario, int *resp);

int remove_arvoreLLRB(arvoreLLRB *raiz, Funcionario funcionario);

struct NO_LLRB *removeNO(struct NO_LLRB *H, Funcionario funcionario);

struct NO_LLRB *removeMenor(struct NO_LLRB *H);

struct NO_LLRB *procuraMenor(struct NO_LLRB *atual);

void confirmeInsercaoLLRB(int x);

#endif // ARVORELLRB_H_INCLUDED
