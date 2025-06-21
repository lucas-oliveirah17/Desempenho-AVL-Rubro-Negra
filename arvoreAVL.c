// Arquivo arvoreAVL.c

#include <stdio.h>
#include <stdlib.h>

#include "teste-desempenho.h"
#include "arvoreAVL.h"
#include "funcionario.h"

struct NO_AVL{
    //int info;
    Funcionario dados;
    int alt; // FB - altura da sub-arvore
    struct NO_AVL *esq;
    struct NO_AVL *dir;
};

arvAVL *cria_arvAVL(){
    arvAVL *raiz = (arvAVL*) malloc(sizeof(arvAVL));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

void liberar_arvAVL(arvAVL *raiz){
    if(raiz == NULL) {
        return;
    }

    // É chamada para liberar cada nó, individualmente.
    libera_NO(*raiz);

    // Após liberar todos os nós, libera a raiz.
    free(raiz);
}

void libera_NO(struct NO_AVL *no){
    if(no == NULL){
        return;
    }

    // Percorre por recursão todos os nós, esquerdos e
    // direitos
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);

    // Armazena NULL em nó para não termos problemas.
    no = NULL; // Não entendi
}

int vazia_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }
    return 0;
}

int altura_arvAVL(arvAVL *raiz){
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
    int alt_esq = altura_arvAVL(&((*raiz)->esq));
    int alt_dir = altura_arvAVL(&((*raiz)->dir));

    // A recursão então vai subindo no retorno somando 1
    // Para saber a altura é necessário percorrer todos
    // os nós.
    if(alt_esq > alt_dir){
        return(alt_esq + 1);
    } else{
        return(alt_dir +1);
    }
}

int totalNO_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = totalNO_arvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_arvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

void preOrdem_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        printf("%d \n", (*raiz)->dados.codigo);
        preOrdem_arvAVL(&((*raiz)->esq));
        preOrdem_arvAVL(&((*raiz)->dir));
    }
}

void emOrdem_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        emOrdem_arvAVL(&((*raiz)->esq));
        printf("%d \n", (*raiz)->dados.codigo);
        emOrdem_arvAVL(&((*raiz)->dir));
    }
}

void posOrdem_arvAVL(arvAVL *raiz){
    // Esse método garante que todos os filhos serão
    // visitados antes de se executar qualquer ação no nó
    // Pai, como por exemplo, a sua exclusão.
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        posOrdem_arvAVL(&((*raiz)->esq));
        posOrdem_arvAVL(&((*raiz)->dir));
        printf("%d \n", (*raiz)->dados.codigo);
    }
}

int consulta_arvAVL(arvAVL*raiz, Funcionario funcionario){
    if(raiz == NULL){
        return 0;
    }
    struct NO_AVL *atual = *raiz;
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

// Código arvore AVL

// Calcula a altura de um nó
int alt_no(struct NO_AVL *no){
    if(no == NULL){
        return -1;
    } else{
        return no->alt;
    }
}

// Devolve o maior entre dois valores
int maior(int x, int y){
    if(x > y){
        return (x);
    } else{
        return (y);
    }
}

// Calcula o Fator de Balanceamento de um nó
int fatorBalanceamento_NO(struct NO_AVL *no){
    // A função abs(), converte o valor passado em seu
    // parâmetro, para o valor absoluto, ou seja, sem sinal.
    return abs(alt_no(no->esq) - alt_no(no->dir));
}

// A função rotaçãoLL(), recebe o nó "A" que foi desbalanceado,
// juntamente com seus filhos esq e dir.
void rotacaoLL(arvAVL *A){
    struct NO_AVL *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    // Calcula a nova altura de "A" em relação ao seus atuais filhos.
    // A nova altura passa a ser a maior altura entre os seus dois filhos
    // +1.
    (*A)->alt = maior(alt_no((*A)->esq), alt_no((*A)->dir)) + 1;
    // A altura do nó "B", passa a ser o maior valor entre o filho da esquerda
    // e a altura do nó "A", que agora é seu filho da direita, +1;
    B->alt = maior(alt_no(B->esq), (*A)->alt) + 1;
    *A = B;
}

// A função rotaçãoR(), recebe o nó "A" que foi desbalanceado,
// juntamente com seus filhos esq e dir.
void rotacaoRR(arvAVL *A){
    struct NO_AVL *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;
    // Calcula a nova altura de "A" em relação ao seus atuais filhos.
    // A nova altura passa a ser a maior altura entre os seus dois filhos
    // +1.
    (*A)->alt = maior(alt_no((*A)->esq), alt_no((*A)->dir)) + 1;
    // A altura do nó "B", passa a ser o maior valor entre o filho da esquerda
    // e a altura do nó "A", que agora é seu filho da direita, +1;
    B->alt = maior(alt_no(B->dir), (*A)->alt) + 1;
    (*A) = B;
}

void rotacaoLR(arvAVL *A){
    rotacaoRR(&(*A)->esq);
    rotacaoLL(A);
}

void rotacaoRL(arvAVL *A){
    rotacaoLL(&(*A)->dir);
    rotacaoRR(A);
}

void confirmeInsercao(int x){
    if(x){
        printf("Elemento inserido com sucesso.\n");
    } else {
        printf("Erro! Elemento nao inserido.\n");
    }
}

// A inserção do elemento na árvore é feita através de chamadas recursivas que
// descem pela árvore, procurando a posição correta, até chegar ao nó da folha,
// quando então, é encontrada a posição a se inserir o elemento.
int insere_arvAVL(arvAVL *raiz, Funcionario funcionario){
    int res; // Armazena as respostas de sucesso do retorno das funções

    // Este "if", é o caso base da recursão: só sera executado quando a chamada
    // recursiva encontrar a posição correta onde inserir o novo nó.
    if(*raiz == NULL){ // Arvore vazia ou chegou no nó folha
        struct NO_AVL *novo;
        novo = (struct NO_AVL*) malloc(sizeof(struct NO_AVL));
        if(novo == NULL){
            return 0;
        }
        // Encontra a posição, preenche-se um nó com sua altura como 0,
        // e seus dois ponteiros como NULL, porque um novo nó, sempre será
        // inserido como uma folha.
        novo->dados = funcionario;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO_AVL *atual = *raiz;
    // Se valor a ser inserido for menor do que campo "info" do Nó atual, a
    // inserção tem que ser feita na esquerda.
    if(funcionario.codigo < atual->dados.codigo){
        // Aqui é o passo recursivo.
        // Se ijsnerção realizada foi ccom sucesso, e a resposta da chamada recursiva
        // (que ficou armazenada em res), for igual a 1, é necessário testar o
        // balanceamento.
        if((res = insere_arvAVL(&(atual->esq), funcionario)) == 1){
            // Testado o fator de balanceamento, se este for maior ou igual a 2, a
            // árvore precisa ser balanceada. Falta apenas saber para que lado o
            // balanceamento terá que ocorrer
            if(fatorBalanceamento_NO(atual) >= 2){
                if(funcionario.codigo < (*raiz)->esq->dados.codigo){
                    // Se o valor é menor, do que o conteúdo do filho da esquerda
                    // da raiz, que é o atual, então é uma inserção deste tipo.
                    rotacaoLL(raiz);
                } else{
                    // Se o valor é maior, do que o conteúdo do filho da esquerda
                    // da raiz, que é o atual, então é uma inserção deste tipo.
                    rotacaoLR(raiz);
                }
            }
        }
    // Trata valores maiores ou iguais
    } else{
        // Se o valor a inserir for maior do que o atual
        if(funcionario.codigo > atual->dados.codigo){
            // Aqui é o passo recursivo.
            if((res = insere_arvAVL(&(atual->dir), funcionario)) == 1){
                //Se inserção OK, chama o Balanceamento e calcula para o nó atual.
                if(fatorBalanceamento_NO(atual) >= 2){
                    // Igual a etapa anterior, este if detecta em que direção a inserção
                    // ocorreu.
                    if((*raiz)->dir->dados.codigo < funcionario.codigo){
                        rotacaoRR(raiz);
                    } else{
                        rotacaoRL(raiz);
                    }
                }
            }
        // Se o valor a inserir não for menor nem maior, ele é igual. Não teremos valores
        // repetidos...
        } else{
            printf("Elemento %d ja existe, Insercao duplicada!\n", funcionario.codigo);
            return 0;
        }
    }
    // Recalcula a altura do nó atual: maior valor entre a altura dos filhos esquerdo e direito,
    // somando +1.
    atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
    return res; // Retorna se inserção OK
}

int remove_arvAVL(arvAVL *raiz, Funcionario funcionario){
    if(*raiz == NULL){
        return 0;
    }
    int res;
    if(funcionario.codigo < (*raiz)->dados.codigo){
        if((res = remove_arvAVL(&(*raiz)->esq, funcionario)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->dir->esq) <= alt_no((*raiz)->dir->dir)){
                    rotacaoRR(raiz);
                } else{
                    rotacaoRL(raiz);
                }
            }
        }
    }
    if((*raiz)->dados.codigo < funcionario.codigo){
        if((res = remove_arvAVL(&(*raiz)->dir, funcionario)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)){
                    rotacaoLL(raiz);
                } else{
                    rotacaoLR(raiz);
                }
            }
        }
    }

    if((*raiz)->dados.codigo == funcionario.codigo){
        if(((*raiz)->esq == NULL) || (*raiz)->dir == NULL){
            struct NO_AVL *no_velho = (*raiz);
            if((*raiz)->esq != NULL){
                *raiz = (*raiz)->esq;
            } else{
                *raiz = (*raiz)->dir;
            }
            free(no_velho);
        } else{
            struct NO_AVL *temp = procuramenor((*raiz)->dir);
            (*raiz)->dados.codigo = temp->dados.codigo;
            remove_arvAVL(&(*raiz)->dir, (*raiz)->dados);
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)){
                    rotacaoLL(raiz);
                } else{
                    rotacaoLR(raiz);
                }
            }
        }
        if(*raiz != NULL){
            (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
        }
        return 1;
    }
    if(*raiz != NULL){
        (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    }
    return res;
}

// Função auxiliar - procura nó mais a esquerda
struct NO_AVL *procuramenor(struct NO_AVL *atual){
    struct NO_AVL *no1 = atual;
    struct NO_AVL *no2 = atual->esq;
    // Procura o nó que está mais a esquerda
    while(no2 != NULL){
        // Enquanto no2 for diferente de NULL, ponteiro se desloca cada vez
        // mais a esquerda. Sempre guardando o último nó visitado no ponteiro
        // no1.
        no1 = no2;
        no2 = no2->esq;
    }
    // Por fim, retorna o último nó válido visitado à esquerda, que é o menor
    // dos maiores elementos que estão a direita do nó a ser removido, que então
    // tomará a sua posição
    return no1;
}

void AVLtoCSV(arvAVL *raiz, FILE *arquivo){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        AVLtoCSV(&((*raiz)->esq), arquivo);
        fprintf(arquivo, "%d;%s;%d;%s;%s;%.2f\n",
            (*raiz)->dados.codigo,
            (*raiz)->dados.nome,
            (*raiz)->dados.idade,
            (*raiz)->dados.empresa,
            (*raiz)->dados.departamento,
            (*raiz)->dados.salario);
        AVLtoCSV(&((*raiz)->dir), arquivo);
    }
}
