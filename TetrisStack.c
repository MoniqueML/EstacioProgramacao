#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[TAM_FILA];
    int inicio, fim, tamanho;
} Fila;

// Estrutura da pilha
typedef struct {
    Peca pecas[TAM_PILHA];
    int topo;
} Pilha;

// ---------- Funções auxiliares ---------- //

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int filaCheia(Fila *f) {
    return f->tamanho == TAM_FILA;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

void enqueue(Fila *f, Peca p) {
    if (!filaCheia(f)) {
        f->fim = (f->fim + 1) % TAM_FILA;
        f->pecas[f->fim] = p;
        f->tamanho++;
    }
}

Peca dequeue(Fila *f) {
    Peca removida = {' ', -1};
    if (!filaVazia(f)) {
        removida = f->pecas[f->inicio];
        f->inicio = (f->inicio + 1) % TAM_FILA;
        f->tamanho--;
    }
    return removida;
}

void push(Pilha *p, Peca nova) {
    if (!pilhaCheia(p)) {
        p->pecas[++p->topo] = nova;
    }
}

Peca pop(Pilha *p) {
    Peca removida = {' ', -1};
    if (!pilhaVazia(p)) {
        removida = p->pecas[p->topo--];
    }
    return removida;
}

// ---------- Exibição ---------- //

void exibirEstado(Fila *f, Pilha *p) {
    printf("\n===== ESTADO ATUAL =====\n");
    printf("Fila de pecas:\t");
    if (filaVazia(f)) printf("(vazia)");
    else {
        for (int i = 0; i < f->tamanho; i++) {
            int idx = (f->inicio + i) % TAM_FILA;
            printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
        }
    }
    printf("\nPilha de reserva (Topo -> Base):\t");
    if (pilhaVazia(p)) printf("(vazia)");
    else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->pecas[i].nome, p->pecas[i].id);
        }
    }
    printf("\n=========================\n\n");
}

// ---------- Operações principais ---------- //

// 1. Jogar peça
void jogarPeca(Fila *f, int *contador) {
    if (!filaVazia(f)) {
        Peca jogada = dequeue(f);
        printf("Jogando peca: [%c %d]\n", jogada.nome, jogada.id);
        enqueue(f, gerarPeca((*contador)++));
    } else {
        printf("Fila vazia! Nenhuma peca para jogar.\n");
    }
}

// 2. Reservar peça (fila → pilha)
void reservarPeca(Fila *f, Pilha *p, int *contador) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Nao e possivel reservar mais pecas.\n");
        return;
    }
    if (!filaVazia(f)) {
        Peca reservada = dequeue(f);
        push(p, reservada);
        printf("Reservando peca: [%c %d]\n", reservada.nome, reservada.id);
        enqueue(f, gerarPeca((*contador)++));
    }
}

// 3. Usar peça reservada (pilha → descarte)
void usarReservada(Pilha *p) {
    if (!pilhaVazia(p)) {
        Peca usada = pop(p);
        printf("Usando peca reservada: [%c %d]\n", usada.nome, usada.id);
    } else {
        printf("Pilha vazia! Nenhuma peca para usar.\n");
    }
}

// 4. Trocar peça da frente da fila com topo da pilha
void trocarUma(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Nao ha pecas suficientes para trocar.\n");
        return;
    }

    int idx = f->inicio;
    Peca temp = f->pecas[idx];
    f->pecas[idx] = p->pecas[p->topo];
    p->pecas[p->topo] = temp;

    printf("Trocando peca da frente da fila com o topo da pilha.\n");
}

// 5. Troca múltipla (3 da fila ↔ 3 da pilha)
void trocaMultipla(Fila *f, Pilha *p) {
    if (f->tamanho < 3 || p->topo < 2) {
        printf("Nao ha pecas suficientes para troca multipla.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idx = (f->inicio + i) % TAM_FILA;
        Peca temp = f->pecas[idx];
        f->pecas[idx] = p->pecas[p->topo - i];
        p->pecas[p->topo - i] = temp;
    }

    printf("Troca multipla realizada entre as 3 primeiras da fila e as 3 da pilha.\n");
}

// ---------- Programa principal ---------- //

int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int contador = 0;

    // Preenche fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(contador++));
    }

    int opcao;
    do {
        exibirEstado(&fila, &pilha);
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Reservar peca (fila -> pilha)\n");
        printf("3 - Usar peca reservada (pilha -> descarte)\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar as 3 primeiras da fila com as 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:
                jogarPeca(&fila, &contador);
                break;
            case 2:
                reservarPeca(&fila, &pilha, &contador);
                break;
            case 3:
                usarReservada(&pilha);
                break;
            case 4:
                trocarUma(&fila, &pilha);
                break;
            case 5:
                trocaMultipla(&fila, &pilha);
                break;
            case 0:
                printf("Encerrando Tetris Stack...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
