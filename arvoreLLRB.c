// Arquivo arvoreLLRB.c

#include <stdio.h>
#include <stdlib.h>

#include "teste-desempenho.h"
#include "arvoreLLRB.h"
#include "funcionario.h"

#define RED 1
#define BLACK 0

struct NO_LLRB{
    Funcionario dados;
    struct NO_LLRB *esq;
    struct NO_LLRB *dir;
    int cor;
};

arvoreLLRB *cria_arvoreLLRB(){
    arvoreLLRB *raiz = (arvoreLLRB*) malloc(sizeof(arvoreLLRB));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

void liberar_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL) {
        return;
    }

    // É chamada para liberar cada nó, individualmente.
    libera_NO_LLRB(*raiz);

    // Após liberar todos os nós, libera a raiz.
    free(raiz);
}

void libera_NO_LLRB(struct NO_LLRB *no){
    if(no == NULL){
        return;
    }

    // Percorre por recursão todos os nós, esquerdos e
    // direitos
    libera_NO_LLRB(no->esq);
    libera_NO_LLRB(no->dir);

    liberar_funcionario(no->dados);

    free(no);
}

int vazia_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }
    return 0;
}

int altura_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        // Quando a recursão descer no nó folha, ela retorna
        // 0. Neste caso altura 0.
        return 0;
    }

    // Passado o endereço do nó, porque a função recursiva
    // espera um ponteiro.
    int alt_esq = altura_arvoreLLRB(&((*raiz)->esq));
    int alt_dir = altura_arvoreLLRB(&((*raiz)->dir));

    // A recursão então vai subindo no retorno somando 1
    // Para saber a altura é necessário percorrer todos
    // os nós.
    if(alt_esq > alt_dir){
        return(alt_esq + 1);
    } else{
        return(alt_dir +1);
    }
}

int totalNO_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = totalNO_arvoreLLRB(&((*raiz)->esq));
    int alt_dir = totalNO_arvoreLLRB(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

void preOrdem_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        printf("%d \n", (*raiz)->dados.codigo);
        preOrdem_arvoreLLRB(&((*raiz)->esq));
        preOrdem_arvoreLLRB(&((*raiz)->dir));
    }
}

void emOrdem_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        emOrdem_arvoreLLRB(&((*raiz)->esq));
        printf("%d \n", (*raiz)->dados.codigo);
        emOrdem_arvoreLLRB(&((*raiz)->dir));
    }
}

void posOrdem_arvoreLLRB(arvoreLLRB *raiz){
    // Esse método garante que todos os filhos serão
    // visitados antes de se executar qualquer ação no nó
    // Pai, como por exemplo, a sua exclusão.
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        posOrdem_arvoreLLRB(&((*raiz)->esq));
        posOrdem_arvoreLLRB(&((*raiz)->dir));
        printf("%d \n", (*raiz)->dados.codigo);
    }
}

int consulta_arvoreLLRB(arvoreLLRB*raiz, Funcionario funcionario){
    if(raiz == NULL){
        return 0;
    }
    struct NO_LLRB *atual = *raiz;
    // Se chegar ao final: atual == NULL, significa
    // que toda a árvore foi percorrida e o elemento
    // não foi encontrado.
    while(atual != NULL){
        if(funcionario.codigo == atual->dados.codigo){
            return 1;
        }
        if(funcionario.codigo > atual->dados.codigo){
            atual = atual->dir;
        } else{
            atual = atual->esq;
        }
    }
    return 0;
}

// Código Árvore Rubro Negra

int cor(struct NO_LLRB *H){
    if(H == NULL){
        return BLACK;
    } else{
        return H->cor;
    }
}

void trocaCor(struct NO_LLRB *H){
    H->cor = !H->cor;
    if(H->esq != NULL){
        H->esq->cor = !H->esq->cor;
    }
    if(H->dir != NULL){
        H->dir->cor = !H->dir->cor;
    }
}

struct NO_LLRB *rotacionaEsquerda(struct NO_LLRB *A){
    struct NO_LLRB *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
};

struct NO_LLRB *rotacionaDireita(struct NO_LLRB *A){
    struct NO_LLRB *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
};

struct NO_LLRB *move2EsqRED(struct NO_LLRB *H){
    trocaCor(H);
    if(cor(H->dir->esq) == RED){
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}

struct NO_LLRB *move2DirRED(struct NO_LLRB *H){
    trocaCor(H);
    if(cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

struct NO_LLRB *balancear(struct NO_LLRB *H){
    if(cor(H->dir) == RED){
        H = rotacionaEsquerda(H);
    }

    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }

    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }

    return H;
}

int insere_arvoreLLRB(arvoreLLRB *raiz, Funcionario funcionario){
    int resp;
    // Função responsável pela busca do lucal de inserção do nó
    *raiz = insereNO(*raiz, funcionario, &resp);
    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }
    return resp;
}

struct NO_LLRB *insereNO(struct NO_LLRB *H, Funcionario funcionario, int *resp){
    if(H == NULL){
        struct NO_LLRB *novo;
        novo = (struct NO_LLRB*) malloc(sizeof(struct NO_LLRB));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }
        novo->dados = funcionario;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    if(funcionario.codigo == H->dados.codigo){
        *resp = 0;
    } else{
        if(funcionario.codigo < H->dados.codigo){
            H->esq = insereNO(H->esq, funcionario, resp);
        } else{
            H->dir = insereNO(H->dir, funcionario, resp);
        }
    }

    if(cor(H->dir) == RED && cor(H->esq) == BLACK){
        H = rotacionaEsquerda(H);
    }

    if(cor(H->esq) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }

    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
}

int remove_arvoreLLRB(arvoreLLRB *raiz, Funcionario funcionario){
    if(consulta_arvoreLLRB(raiz, funcionario)){
        struct NO_LLRB *H = *raiz;
        // Função responsável pela busca pelo nó a ser removido
        *raiz = removeNO(H, funcionario);
        if(*raiz != NULL){
            (*raiz)->cor = BLACK;
        }
        return 1;
    } else{
        return 0;
    }
}

struct NO_LLRB *removeNO(struct NO_LLRB *H, Funcionario funcionario){
    if(funcionario.codigo < H->dados.codigo){
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
            H = move2EsqRED(H);
        }
        H->esq = removeNO(H->esq, funcionario);
    }

    else{
        if(cor(H->esq) == RED){
            H = rotacionaDireita(H);
        }

        if(funcionario.codigo == H->dados.codigo && (H->dir == NULL)){
            free(H);
            return NULL;
        }

        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK){
            H = move2DirRED(H);
        }

        if(funcionario.codigo == H->dados.codigo){
            struct NO_LLRB *x = procuraMenor(H->dir);
            H->dados = x->dados;
            H->dir = removeMenor(H->dir);
        } else{
            H->dir = removeNO(H->dir, funcionario);
        }
    }
    return balancear(H);
}

struct NO_LLRB *removeMenor(struct NO_LLRB *H){
    if(H->esq == NULL){
        free(H);
        return NULL;
    }

    if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
        H = move2EsqRED(H);
    }

    H->esq = removeMenor(H->esq);
    return balancear(H);
}

struct NO_LLRB *procuraMenor(struct NO_LLRB *atual){
    struct NO_LLRB *no1 = atual;
    struct NO_LLRB *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

void confirmeInsercaoLLRB(int x){
    if(x){
        printf("Elemento inserido com sucesso.\n");
    } else {
        printf("Erro! Elemento nao inserido.\n");
    }
}

void LLRBtoCSV(arvoreLLRB *raiz, FILE *arquivo){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        LLRBtoCSV(&((*raiz)->esq), arquivo);
        fprintf(arquivo, "%d;%s;%d;%s;%s;%.2f\n",
            (*raiz)->dados.codigo,
            (*raiz)->dados.nome,
            (*raiz)->dados.idade,
            (*raiz)->dados.empresa,
            (*raiz)->dados.departamento,
            (*raiz)->dados.salario);
        LLRBtoCSV(&((*raiz)->dir), arquivo);
    }
}
