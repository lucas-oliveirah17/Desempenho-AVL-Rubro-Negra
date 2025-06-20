// Arquivo arvoreAVL.h
#include "teste-desempenho.h"

typedef struct NO_AVL *arvAVL;

arvAVL *cria_arvAVL();

void liberar_arvAVL(arvAVL *raiz);

void libera_NO(struct NO_AVL *no);

int vazia_arvAVL(arvAVL *raiz);

int altura_arvAVL(arvAVL *raiz);

int totalNO_arvAVL(arvAVL *raiz);

void preOrdem_arvAVL(arvAVL *raiz);

void emOrdem_arvAVL(arvAVL *raiz);

void posOrdem_arvAVL(arvAVL *raiz);

struct NO_AVL *remove_atual(struct NO_AVL *atual);

int consulta_arvAVL(arvAVL*raiz, Funcionario funcionario);

// Código arvore AVL

int alt_no(struct NO_AVL *no);

int maior(int x, int y);

int fatorBalanceamento_NO(struct NO_AVL *no);

void rotacaoLL(arvAVL *A);

void rotacaoRR(arvAVL *A);

void rotacaoLR(arvAVL *A);

void rotacaoRL(arvAVL *A);

int insere_arvAVL(arvAVL *raiz, Funcionario funcionario);

void confirmeInsercao(int x);

int remove_arvAVL(arvAVL *raiz, Funcionario funcionario);

struct NO_AVL *procuramenor(struct NO_AVL *atual);

