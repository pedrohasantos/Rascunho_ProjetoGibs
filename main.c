#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINHAS 2
#define COLUNAS 5
#define PARES 5

typedef struct NoDupla {
    char data;
    struct NoDupla *prox;
    struct NoDupla *ante;
} NoDupla;

typedef struct NoSimples {
    char data;
    struct NoSimples *prox;
} NoSimples;

typedef struct NoCircular {
    int linha;
    int coluna;
    struct NoCircular *prox;
} NoCircular;

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

NoCircular *criarNo_Circular(int linha, int coluna) {
    NoCircular *novoNo = (NoCircular*)malloc(sizeof(NoCircular));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->linha = linha;
    novoNo->coluna = coluna;
    novoNo->prox = novoNo;
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

void inserir_fim_circular(NoCircular **lista, int linha, int coluna) {
    NoCircular *novoNo = criarNo_Circular(linha, coluna);
    if (*lista == NULL) {
        *lista = novoNo;
    } else {
        NoCircular *temp = *lista;
        while (temp->prox != *lista) {
            temp = temp->prox;
        }
        temp->prox = novoNo;
        novoNo->prox = *lista;
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

void imprimir_lista_circular(NoCircular *lista) {
    if (lista == NULL) return;
    NoCircular *temp = lista;
    do {
        printf("(%d, %d) ", temp->linha, temp->coluna);
        temp = temp->prox;
    } while (temp != lista);
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

int hash_mod(int i){
    return i % (LINHAS * COLUNAS);
}

char vogais[] = {'A', 'E', 'I', 'O', 'U'};

void iniciar_cartas(char cartas[LINHAS][COLUNAS], bool revelada[LINHAS][COLUNAS]){
    int i, j, k;
    
    for(i = 0; i < LINHAS; i++){
        for(j = 0; j < COLUNAS; j++){
            cartas[i][j] = '\0';
            revelada[i][j] = false;
        }
    }
    
    for(i = 0; i < PARES; i++){
        for(j = 0; j < 2; j++){
            int pos;
            do{
                pos = hash_mod(rand());
            } while (cartas[pos / COLUNAS][pos % COLUNAS] != '\0');
            
            cartas[pos / COLUNAS][pos % COLUNAS] = vogais[i];
        }
    }
}

void iniciar_jogo(char cartas[LINHAS][COLUNAS], bool revelada[LINHAS][COLUNAS]){
    int i, j;
    printf("\n   ");
    for (i = 0; i < COLUNAS; i++) {
        printf(" %d ", i);
    }
    printf("\n");

    for (i = 0; i < LINHAS; i++) {
        printf(" %d ", i);
        for (j = 0; j < COLUNAS; j++) {
            if (revelada[i][j]) {
                printf(" %c ", cartas[i][j]);
            } else {
                printf(" ? ");
            }
        }
        printf("\n");
    }
}

void checar_tentativas(NoCircular *tentativas, char cartas[LINHAS][COLUNAS], bool revelada[LINHAS][COLUNAS]) {
    if (tentativas == NULL || tentativas->prox == tentativas) return; // Verifica se existem duas tentativas
    
    NoCircular *primeira = tentativas;
    NoCircular *segunda = tentativas->prox;
    
    if (cartas[primeira->linha][primeira->coluna] == cartas[segunda->linha][segunda->coluna]) {
        revelada[primeira->linha][primeira->coluna] = true;
        revelada[segunda->linha][segunda->coluna] = true;
        printf("Par encontrado!\n");
    } else {
        printf("Cartas diferentes. Tente novamente.\n");
    }
}

void resetar_jogo(NoCircular **tentativas) {
    if (*tentativas != NULL) {
        NoCircular *temp = *tentativas;
        NoCircular *proxNo;
        do {
            proxNo = temp->prox;
            free(temp);
            temp = proxNo;
        } while (temp != *tentativas);
        *tentativas = NULL;
    }
}

int main() {
    printf("\t BEM VINDO AO JOGO DA MEMÓRIA!\n");
    //eu sei que criança não sabe ler, mas é só para ficar bonitinho
    printf("(1) JOGAR!\n");
    printf("(2) SAIR!\n");
    
    NoSimples *listaSimples = NULL;
    NoDupla *listaDupla = NULL;
    
    char cartas[LINHAS][COLUNAS];
    bool revelada[LINHAS][COLUNAS];
    
    int opsStart, opsJogo;
    NoCircular *tentativas = NULL;
    printf("Gostaria de jogar? (1 para sim, 2 para não): \n");
    scanf("%d", &opsStart);
    
    do {
        switch(opsStart) {
            case 1:
                iniciar_cartas(cartas, revelada);
                do {
                    printf("Digite a opção que você gostaria:\n");
                    printf("(1) Iniciar jogo\n");
                    printf("(2) Fazer uma tentativa\n");
                    printf("(0) Sair\n");
                    scanf("%d", &opsJogo);
                    int linha, coluna;
                    switch(opsJogo) {
                        case 1:
                            iniciar_jogo(cartas, revelada);
                            break;
                        case 2:
                            printf("Digite a linha e coluna da carta: ");
                            scanf("%d %d", &linha, &coluna);
                            inserir_fim_circular(&tentativas, linha, coluna);
                            if (tentativas->prox != tentativas) {
                                checar_tentativas(tentativas, cartas, revelada);
                                resetar_jogo(&tentativas);
                            }
                            iniciar_jogo(cartas, revelada);
                            break;
                        case 0:
                            printf("Saindo...\n");
                            break;
                        default:
                            printf("Opção inválida, digite novamente sua opção: \n");
                            break;
                    }
                } while(opsJogo != 0);
                break;
            case 2:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida, digite novamente sua opção: \n");
                scanf("%d", &opsStart);
                break;
        }
    } while(opsStart != 2);

    return 0;
}
