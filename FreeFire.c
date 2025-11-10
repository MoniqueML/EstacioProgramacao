#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

// Estrutura base do componente
struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
};
typedef struct Componente Componente;

// ==================== FUNÇÕES DE SUPORTE ====================

// Exibe todos os componentes cadastrados
void mostrarComponentes(Componente comp[], int n) {
    printf("\n=== COMPONENTES ATUAIS ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d - Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
    printf("===========================\n\n");
}

// ==================== BUBBLE SORT (por nome) ====================
int bubbleSortNome(Componente comp[], int n) {
    int comparacoes = 0;
    Componente temp;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(comp[j].nome, comp[j + 1].nome) > 0) {
                temp = comp[j];
                comp[j] = comp[j + 1];
                comp[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}

// ==================== INSERTION SORT (por tipo) ====================
int insertionSortTipo(Componente comp[], int n) {
    int comparacoes = 0;
    Componente chave;

    for (int i = 1; i < n; i++) {
        chave = comp[i];
        int j = i - 1;

        while (j >= 0 && strcmp(comp[j].tipo, chave.tipo) > 0) {
            comp[j + 1] = comp[j];
            j--;
            comparacoes++;
        }
        comp[j + 1] = chave;
        comparacoes++;
    }
    return comparacoes;
}

// ==================== SELECTION SORT (por prioridade) ====================
int selectionSortPrioridade(Componente comp[], int n) {
    int comparacoes = 0;
    int min;
    Componente temp;

    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (comp[j].prioridade < comp[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            temp = comp[i];
            comp[i] = comp[min];
            comp[min] = temp;
        }
    }
    return comparacoes;
}

// ==================== BUSCA BINÁRIA (por nome) ====================
int buscaBinariaPorNome(Componente comp[], int n, char chave[]) {
    int inicio = 0, fim = n - 1, meio;
    int comparacoes = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(chave, comp[meio].nome);

        if (cmp == 0) {
            printf("Componente encontrado: %s | %s | %d\n",
                   comp[meio].nome, comp[meio].tipo, comp[meio].prioridade);
            printf("Comparacoes feitas na busca: %d\n\n", comparacoes);
            return meio;
        } else if (cmp > 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Componente nao encontrado. Comparacoes: %d\n\n", comparacoes);
    return -1;
}

// ==================== CADASTRAR COMPONENTES ====================
int cadastrarComponentes(Componente comp[]) {
    int n;
    printf("Quantos componentes deseja cadastrar (max %d)? ", MAX_COMP);
    scanf("%d", &n);
    getchar(); // limpar buffer

    if (n > MAX_COMP) n = MAX_COMP;

    for (int i = 0; i < n; i++) {
        printf("\nComponente %d:\n", i + 1);
        printf("Nome: ");
        fgets(comp[i].nome, 30, stdin);
        comp[i].nome[strcspn(comp[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(comp[i].tipo, 20, stdin);
        comp[i].tipo[strcspn(comp[i].tipo, "\n")] = '\0';

        printf("Prioridade (1-10): ");
        scanf("%d", &comp[i].prioridade);
        getchar();
    }

    printf("\nCadastro concluido!\n");
    mostrarComponentes(comp, n);
    return n;
}

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    Componente componentes[MAX_COMP];
    int total = 0;
    int opcao;
    clock_t inicio, fim;
    double tempo;
    int comparacoes;
    char nomeBusca[30];

    do {
        printf("=== SISTEMA DE MONTAGEM DA TORRE DE FUGA ===\n");
        printf("1 - Cadastrar componentes\n");
        printf("2 - Ordenar por NOME (Bubble Sort)\n");
        printf("3 - Ordenar por TIPO (Insertion Sort)\n");
        printf("4 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5 - Buscar componente-chave (Busca Binaria - somente após ordenacao por nome)\n");
        printf("6 - Mostrar componentes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                total = cadastrarComponentes(componentes);
                break;

            case 2:
                inicio = clock();
                comparacoes = bubbleSortNome(componentes, total);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nOrdenado por NOME (Bubble Sort)\nComparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                mostrarComponentes(componentes, total);
                break;

            case 3:
                inicio = clock();
                comparacoes = insertionSortTipo(componentes, total);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nOrdenado por TIPO (Insertion Sort)\nComparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                mostrarComponentes(componentes, total);
                break;

            case 4:
                inicio = clock();
                comparacoes = selectionSortPrioridade(componentes, total);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nOrdenado por PRIORIDADE (Selection Sort)\nComparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                mostrarComponentes(componentes, total);
                break;

            case 5:
                printf("Digite o nome do componente-chave: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                buscaBinariaPorNome(componentes, total, nomeBusca);
                break;

            case 6:
                mostrarComponentes(componentes, total);
                break;
        }

    } while (opcao != 0);

    printf("\n=== Fim da simulacao ===\n");
    printf("Torre de fuga montada com sucesso! 🚀\n");
    return 0;
}
