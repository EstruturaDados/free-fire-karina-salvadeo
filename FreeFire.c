#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// ============================================================================
//         Código da Ilha – Edição Free Fire
// ============================================================================
// Karina Salvadeo Pereira - Engenharia de Software (Estrutura de Dados)       
// ============================================================================

// Estrutura que representa um item na mochila
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // Valor de 1 a 5
};

// Capacidade máxima da mochila
const int MAX_ITENS = 10;

// Enumeração para critérios de ordenação
enum CriterioOrdenacao {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
};

// Função para exibir o menu
void mostrarMenu() {
    printf("\n=== MENU DO INVENTARIO ===\n");
    printf("1 - Adicionar item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Ordenar itens\n");
    printf("5 - Buscar item por nome (busca binaria)\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para adicionar um item
void adicionarItem(struct Item mochila[], int *totalItens) {
    if (*totalItens < MAX_ITENS) {
        printf("Digite o nome do item: ");
        scanf(" %[^\n]", mochila[*totalItens].nome);

        printf("Digite o tipo do item: ");
        scanf(" %[^\n]", mochila[*totalItens].tipo);

        printf("Digite a quantidade: ");
        scanf("%d", &mochila[*totalItens].quantidade);

        do {
            printf("Digite a prioridade (1 a 5): ");
            scanf("%d", &mochila[*totalItens].prioridade);
        } while (mochila[*totalItens].prioridade < 1 || mochila[*totalItens].prioridade > 5);

        (*totalItens)++;
        printf("Item adicionado com sucesso!\n");
    } else {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
    }
}

// Função para remover item
void removerItem(struct Item mochila[], int *totalItens) {
    char nomeRemover[30];
    int encontrado = 0;

    printf("Digite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*totalItens)--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Item nao encontrado.\n");
    }
}

// Função para listar itens
void listarItens(struct Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        printf("\n--- Itens na mochila ---\n");
        printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Quantidade", "Prioridade");
        for (int i = 0; i < totalItens; i++) {
            printf("%-20s %-15s %-10d %-10d\n", 
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
        }
    }
}

// Função para comparar dois itens de acordo com o critério
int comparar(struct Item a, struct Item b, enum CriterioOrdenacao criterio, int *comparacoes) {
    (*comparacoes)++; // Conta cada comparação feita

    switch(criterio) {
        case ORDENAR_NOME: return strcmp(a.nome, b.nome);
        case ORDENAR_TIPO: return strcmp(a.tipo, b.tipo);
        case ORDENAR_PRIORIDADE: return a.prioridade - b.prioridade;
        default: return 0;
    }
}

// Função para ordenar itens com Insertion Sort
void ordenarItens(struct Item mochila[], int totalItens, enum CriterioOrdenacao criterio, int *comparacoes) {
    *comparacoes = 0; // Zera contador de comparações

    for (int i = 1; i < totalItens; i++) {
        struct Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0 && comparar(mochila[j], chave, criterio, comparacoes) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }

    printf("Itens ordenados com sucesso!\n");
    printf("Total de comparacoes realizadas: %d\n", *comparacoes);
}

// Função de busca binária por nome
int buscaBinaria(struct Item mochila[], int totalItens, char nomeBusca[]) {
    int esquerda = 0, direita = totalItens - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) {
            return meio; // Item encontrado
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1; // Não encontrado
}

int main() {
    struct Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;
    bool ordenadoPorNome = false; // Controle se a mochila está ordenada por nome

    do {
        mostrarMenu();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: 
                adicionarItem(mochila, &totalItens); 
                ordenadoPorNome = false; // Nova inserção quebra a ordenação
                break;

            case 2: 
                removerItem(mochila, &totalItens); 
                ordenadoPorNome = false; // Remoção quebra a ordenação
                break;

            case 3: 
                listarItens(mochila, totalItens); 
                break;

            case 4: { // Ordenar
                int criterio, comparacoes;
                printf("Escolha o criterio de ordenacao:\n");
                printf("1 - Nome\n2 - Tipo\n3 - Prioridade\n");
                scanf("%d", &criterio);

                ordenarItens(mochila, totalItens, criterio, &comparacoes);
                if (criterio == ORDENAR_NOME) {
                    ordenadoPorNome = true;
                } else {
                    ordenadoPorNome = false;
                }
                break;
            }

            case 5: { // Busca binária
                if (!ordenadoPorNome) {
                    printf("A lista deve estar ordenada por NOME antes da busca binaria.\n");
                } else {
                    char nomeBusca[30];
                    printf("Digite o nome do item para buscar: ");
                    scanf(" %[^\n]", nomeBusca);

                    int indice = buscaBinaria(mochila, totalItens, nomeBusca);
                    if (indice != -1) {
                        printf("\n--- Item encontrado ---\n");
                        printf("Nome: %s\n", mochila[indice].nome);
                        printf("Tipo: %s\n", mochila[indice].tipo);
                        printf("Quantidade: %d\n", mochila[indice].quantidade);
                        printf("Prioridade: %d\n", mochila[indice].prioridade);
                    } else {
                        printf("Item nao encontrado.\n");
                    }
                }
                break;
            }

            case 0: 
                printf("Encerrando o programa...\n"); 
                break;

            default: 
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}

