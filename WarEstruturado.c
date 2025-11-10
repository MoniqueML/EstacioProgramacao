#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};
typedef struct Territorio Territorio;

// Função que cadastra os territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("Cadastro do territorio %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

// Exibe os territórios cadastrados
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== Territorios ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

// Simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nAtaque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("O defensor resistiu!\n");
        atacante->tropas -= 1;
    }
    printf("\n");
}

// Sorteia uma missão para o jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Mostra a missão do jogador
void exibirMissao(char* missao) {
    printf("\nSua missao: %s\n\n", missao);
}

// Verifica se a missão foi cumprida (lógica simples inicial)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo de verificação simples
    if (strstr(missao, "vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0; // ainda existe território vermelho
            }
        }
        return 1; // missão cumprida
    }
    return 0;
}

// Libera memória alocada
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
}

int main() {
    srand(time(NULL));

    int n;
    printf("Digite o numero de territorios: ");
    scanf("%d", &n);

    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    cadastrarTerritorios(mapa, n);

    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar metade do mapa",
        "Vencer 2 batalhas consecutivas",
        "Ter mais de 20 tropas em um territorio"
    };
    int totalMissoes = 5;

    // Missões alocadas dinamicamente
    char* missaoJogador1 = (char*) malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*) malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("\n--- Jogador 1 ---");
    exibirMissao(missaoJogador1);

    printf("--- Jogador 2 ---");
    exibirMissao(missaoJogador2);

    int atacante, defensor;
    int turno = 1;
    int vencedor = 0;

    while (!vencedor) {
        printf("\n=== Turno %d ===\n", turno);
        exibirTerritorios(mapa, n);

        printf("Jogador %d, escolha o territorio atacante: ", (turno % 2) ? 1 : 2);
        scanf("%d", &atacante);
        printf("Escolha o territorio defensor: ");
        scanf("%d", &defensor);

        if (strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0) {
            printf("Nao pode atacar um territorio da mesma cor!\n");
        } else {
            atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
        }

        // Verifica se alguém cumpriu a missão
        if (verificarMissao(missaoJogador1, mapa, n)) {
            printf("\n*** Jogador 1 venceu cumprindo sua missao! ***\n");
            vencedor = 1;
        } else if (verificarMissao(missaoJogador2, mapa, n)) {
            printf("\n*** Jogador 2 venceu cumprindo sua missao! ***\n");
            vencedor = 1;
        }

        turno++;
        if (turno > 50) { // limite de segurança
            printf("Jogo encerrado por tempo limite.\n");
            break;
        }
    }

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    return 0;
}
