#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    NoSimples *listaSimples = NULL;
    NoDupla *listaDupla = NULL;
    printf("Hello world!")
    
    return 0;
}
