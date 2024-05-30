#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define coberto 0
#define descoberto 1

int jogo 1[2] [5] = {
    1, 2, 3, 4, 5, 
    6, 7, 8, 9, 0 
        };//onde ficarão as cartas. depois ver como mudar para hashing

int jogo 2[2] [5] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
    }; //para saber se já foi descoberto ou não
    
void monta();
void analiza();


typedef struct NoDupla {
    char data;
    struct NoDupla *prox;
    struct NoDupla *ante;
} NoDupla;

typedef struct NoSimples {
    char data;
    struct NoSimples *prox;
} NoSimples;

NoSimples *criarNo_Simples(char c) {
    NoSimples *novoNo = (NoSimples*)malloc(sizeof(NoSimples));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->data = c;
    novoNo->prox = NULL;
    return novoNo;
}

NoDupla *criarNo_Dupla(char c) {
    NoDupla *novoNo = (NoDupla*)malloc(sizeof(NoDupla));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->data = c;
    novoNo->prox = NULL;
    novoNo->ante = NULL;
    return novoNo;
}

void inserir_fim_simples(NoSimples **lista, char c) {
    NoSimples *novoNo = criarNo_Simples(c);
    if (*lista == NULL) {
        *lista = novoNo;
    } else {
        NoSimples *temp = *lista;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novoNo;
    }
}

void inserir_fim_dupla(NoDupla **lista, char c) {
    NoDupla *novoNo = criarNo_Dupla(c);
    if (*lista == NULL) {
        *lista = novoNo;
    } else {
        NoDupla *temp = *lista;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novoNo;
        novoNo->ante = temp;
    }
}

void imprimir_lista_simples(NoSimples *lista) {
    NoSimples *temp = lista;
    while (temp != NULL) {
        printf("%c ", temp->data);
        temp = temp->prox;
    }
    printf("\n");
}

void imprimir_lista_dupla(NoDupla *lista) {
    NoDupla *temp = lista;
    while (temp != NULL) {
        printf("%c ", temp->data);
        temp = temp->prox;
    }
    printf("\n");
}
void remover_no_simples(NoSimples **lista, char c) {
    if (*lista == NULL) return;

    NoSimples *temp = *lista;
    NoSimples *anterior = NULL;

    while (temp != NULL && temp->data != c) {
        anterior = temp;
        temp = temp->prox;
    }
    if (anterior == NULL) {
        // Remover o primeiro nó
        *lista = temp->prox;  
    } else {
        // Remover um nó no meio ou no final
        anterior->prox = temp->prox;  
    }
    free(temp);
}

void remover_no_dupla(NoDupla **lista, char c) {
    if (*lista == NULL) return;
    NoDupla *temp = *lista;
    while (temp != NULL && temp->data != c) {
        temp = temp->prox;
    }
    if (temp->ante == NULL) {
        // Remover o primeiro nó
        *lista = temp->prox;
        if (temp->prox != NULL) {
            temp->prox->ante = NULL;
        }
    } else {
        // Remover um nó no meio ou no final
        temp->ante->prox = temp->prox;
        if (temp->prox != NULL) {
            temp->prox->ante = temp->ante;
        }
    }
    free(temp);
}
void options(){
    printf("1. Feijão\n2. Arroz\n3. batata\n");
}
int main() {

    printf("\t BEM VINDO AO JOGO DA MEMÓRIA!");
    //eu sei que criança não sabe ler, mas é só para ficar bonitinho
    printf("Digite a opção que você gostaria: \n");
    print("(1) JOGAR!\n");
    printf("(2) SAIR!\n");
    
    NoSimples *listaSimples = NULL;
    NoDupla *listaDupla = NULL;
    int ops;
    do{
        printf("Digite a opção que você gostaria: \n");
        options();
        scanf("%d",&ops);
            switch(ops){
                case 1:
                case 2:
                case 0:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opção inválida, digite novamente sua opção: \n");
            }
    }while(ops!=0);
    printf("Hello world!");
    
    return 0;
}
