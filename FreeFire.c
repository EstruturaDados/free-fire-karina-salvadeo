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
    char nome[30];     // Nome do item
    char tipo[20];     // Tipo do item
    int quantidade;    // Quantidade do item
};

int main() {
    struct Item mochila[10]; // Vetor estático com capacidade para 10 itens
    int totalItens = 0;      // Contador de quantos itens estão cadastrados
    int opcao;               // Variável para armazenar a escolha do menu

    // Laço principal do menu
    do {
        // Exibe as opções para o usuário
        printf("\n=== MENU DO INVENTARIO ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao); // Lê a opção escolhida

        switch(opcao) {
            case 1: // Adicionar item
                if (totalItens < 10) { // Verifica se há espaço na mochila
                    printf("Digite o nome do item: ");
                    scanf(" %[^\n]", mochila[totalItens].nome); // Lê o nome com espaços

                    printf("Digite o tipo do item: ");
                    scanf(" %[^\n]", mochila[totalItens].tipo); // Lê o tipo com espaços

                    printf("Digite a quantidade: ");
                    scanf("%d", &mochila[totalItens].quantidade); // Lê a quantidade

                    totalItens++; // Incrementa o número de itens cadastrados
                    printf("Item adicionado com sucesso!\n");
                } else {
                    printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
                }
                break;

            case 2: { // Remover item
                char nomeRemover[30]; // Nome do item a ser removido
                int encontrado = 0;   // Flag para indicar se o item foi encontrado

                printf("Digite o nome do item que deseja remover: ");
                scanf(" %[^\n]", nomeRemover); // Lê o nome

                for (int i = 0; i < totalItens; i++) { // Percorre os itens cadastrados
                    if (strcmp(mochila[i].nome, nomeRemover) == 0) { // Compara nomes
                        // Sobrescreve o item removido com o próximo
                        for (int j = i; j < totalItens - 1; j++) {
                            mochila[j] = mochila[j + 1];
                        }
                        totalItens--; // Reduz o total de itens
                        encontrado = 1; // Marca que o item foi encontrado
                        printf("Item removido com sucesso!\n");
                        break; // Sai do laço após remover
                    }
                }
                if (!encontrado) {
                    printf("Item nao encontrado.\n");
                }
                break;
            }

            case 3: // Listar itens
                if (totalItens == 0) {
                    printf("A mochila esta vazia.\n");
                } else {
                    printf("\n--- Itens na mochila ---\n");
                    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade"); // Cabeçalho
                    for (int i = 0; i < totalItens; i++) {
                        printf("%-20s %-15s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                    }
                }
                break;

            case 0: // Sair do programa
                printf("Encerrando o programa...\n");
                break;

            default: // Caso inválido
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while(opcao != 0); // Repete enquanto o usuário não escolher sair

    return 0; // Fim do programa
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
