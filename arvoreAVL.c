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

    // � chamada para liberar cada n�, individualmente.
    libera_NO(*raiz);

    // Ap�s liberar todos os n�s, libera a raiz.
    free(raiz);
}

void libera_NO(struct NO_AVL *no){
    if(no == NULL){
        return;
    }

    // Percorre por recurs�o todos os n�s, esquerdos e
    // direitos
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);

    // Armazena NULL em n� para n�o termos problemas.
    no = NULL; // N�o entendi
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
        // Quando a recurs�o descer no n� folha, ela retorna
        // 0. Neste caso altura 0.
        return 0;
    }

    // Passado o endere�o do n�, porque a fun��o recursiva
    // espera um ponteiro.
    int alt_esq = altura_arvAVL(&((*raiz)->esq));
    int alt_dir = altura_arvAVL(&((*raiz)->dir));

    // A recurs�o ent�o vai subindo no retorno somando 1
    // Para saber a altura � necess�rio percorrer todos
    // os n�s.
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
    // Esse m�todo garante que todos os filhos ser�o
    // visitados antes de se executar qualquer a��o no n�
    // Pai, como por exemplo, a sua exclus�o.
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
    // que toda a �rvore foi percorrida e o elemento
    // n�o foi encontrado.
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

// C�digo arvore AVL

// Calcula a altura de um n�
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

// Calcula o Fator de Balanceamento de um n�
int fatorBalanceamento_NO(struct NO_AVL *no){
    // A fun��o abs(), converte o valor passado em seu
    // par�metro, para o valor absoluto, ou seja, sem sinal.
    return abs(alt_no(no->esq) - alt_no(no->dir));
}

// A fun��o rota��oLL(), recebe o n� "A" que foi desbalanceado,
// juntamente com seus filhos esq e dir.
void rotacaoLL(arvAVL *A){
    struct NO_AVL *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    // Calcula a nova altura de "A" em rela��o ao seus atuais filhos.
    // A nova altura passa a ser a maior altura entre os seus dois filhos
    // +1.
    (*A)->alt = maior(alt_no((*A)->esq), alt_no((*A)->dir)) + 1;
    // A altura do n� "B", passa a ser o maior valor entre o filho da esquerda
    // e a altura do n� "A", que agora � seu filho da direita, +1;
    B->alt = maior(alt_no(B->esq), (*A)->alt) + 1;
    *A = B;
}

// A fun��o rota��oR(), recebe o n� "A" que foi desbalanceado,
// juntamente com seus filhos esq e dir.
void rotacaoRR(arvAVL *A){
    struct NO_AVL *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;
    // Calcula a nova altura de "A" em rela��o ao seus atuais filhos.
    // A nova altura passa a ser a maior altura entre os seus dois filhos
    // +1.
    (*A)->alt = maior(alt_no((*A)->esq), alt_no((*A)->dir)) + 1;
    // A altura do n� "B", passa a ser o maior valor entre o filho da esquerda
    // e a altura do n� "A", que agora � seu filho da direita, +1;
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

// A inser��o do elemento na �rvore � feita atrav�s de chamadas recursivas que
// descem pela �rvore, procurando a posi��o correta, at� chegar ao n� da folha,
// quando ent�o, � encontrada a posi��o a se inserir o elemento.
int insere_arvAVL(arvAVL *raiz, Funcionario funcionario){
    int res; // Armazena as respostas de sucesso do retorno das fun��es

    // Este "if", � o caso base da recurs�o: s� sera executado quando a chamada
    // recursiva encontrar a posi��o correta onde inserir o novo n�.
    if(*raiz == NULL){ // Arvore vazia ou chegou no n� folha
        struct NO_AVL *novo;
        novo = (struct NO_AVL*) malloc(sizeof(struct NO_AVL));
        if(novo == NULL){
            return 0;
        }
        // Encontra a posi��o, preenche-se um n� com sua altura como 0,
        // e seus dois ponteiros como NULL, porque um novo n�, sempre ser�
        // inserido como uma folha.
        novo->dados = funcionario;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO_AVL *atual = *raiz;
    // Se valor a ser inserido for menor do que campo "info" do N� atual, a
    // inser��o tem que ser feita na esquerda.
    if(funcionario.codigo < atual->dados.codigo){
        // Aqui � o passo recursivo.
        // Se ijsner��o realizada foi ccom sucesso, e a resposta da chamada recursiva
        // (que ficou armazenada em res), for igual a 1, � necess�rio testar o
        // balanceamento.
        if((res = insere_arvAVL(&(atual->esq), funcionario)) == 1){
            // Testado o fator de balanceamento, se este for maior ou igual a 2, a
            // �rvore precisa ser balanceada. Falta apenas saber para que lado o
            // balanceamento ter� que ocorrer
            if(fatorBalanceamento_NO(atual) >= 2){
                if(funcionario.codigo < (*raiz)->esq->dados.codigo){
                    // Se o valor � menor, do que o conte�do do filho da esquerda
                    // da raiz, que � o atual, ent�o � uma inser��o deste tipo.
                    rotacaoLL(raiz);
                } else{
                    // Se o valor � maior, do que o conte�do do filho da esquerda
                    // da raiz, que � o atual, ent�o � uma inser��o deste tipo.
                    rotacaoLR(raiz);
                }
            }
        }
    // Trata valores maiores ou iguais
    } else{
        // Se o valor a inserir for maior do que o atual
        if(funcionario.codigo > atual->dados.codigo){
            // Aqui � o passo recursivo.
            if((res = insere_arvAVL(&(atual->dir), funcionario)) == 1){
                //Se inser��o OK, chama o Balanceamento e calcula para o n� atual.
                if(fatorBalanceamento_NO(atual) >= 2){
                    // Igual a etapa anterior, este if detecta em que dire��o a inser��o
                    // ocorreu.
                    if((*raiz)->dir->dados.codigo < funcionario.codigo){
                        rotacaoRR(raiz);
                    } else{
                        rotacaoRL(raiz);
                    }
                }
            }
        // Se o valor a inserir n�o for menor nem maior, ele � igual. N�o teremos valores
        // repetidos...
        } else{
            printf("Elemento %d ja existe, Insercao duplicada!\n", funcionario.codigo);
            return 0;
        }
    }
    // Recalcula a altura do n� atual: maior valor entre a altura dos filhos esquerdo e direito,
    // somando +1.
    atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
    return res; // Retorna se inser��o OK
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

// Fun��o auxiliar - procura n� mais a esquerda
struct NO_AVL *procuramenor(struct NO_AVL *atual){
    struct NO_AVL *no1 = atual;
    struct NO_AVL *no2 = atual->esq;
    // Procura o n� que est� mais a esquerda
    while(no2 != NULL){
        // Enquanto no2 for diferente de NULL, ponteiro se desloca cada vez
        // mais a esquerda. Sempre guardando o �ltimo n� visitado no ponteiro
        // no1.
        no1 = no2;
        no2 = no2->esq;
    }
    // Por fim, retorna o �ltimo n� v�lido visitado � esquerda, que � o menor
    // dos maiores elementos que est�o a direita do n� a ser removido, que ent�o
    // tomar� a sua posi��o
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
