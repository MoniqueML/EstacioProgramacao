#include <stdio.h>

// Função: mover a Torre para a direita
void moverTorre(int casasRestantes) {
    if (casasRestantes == 0) {
        return; // parada
    }
    printf("Direita\n");
    moverTorre(casasRestantes - 1); 
}

// Função: mover a Rainha para a esquerda
void moverRainha(int casasRestantes) {
    if (casasRestantes == 0) {
        return; // parada
    }
    printf("Esquerda\n");
    moverRainha(casasRestantes - 1); 
}

// Função para mover o Bispo
// Movimento diagonal: vertical para cima, horizontal para direita
// número de casas na vertical e horizontal para percorrer
void moverBispoRecursivo(int casasVerticais, int casasHorizontais) {
    if (casasVerticais == 0 || casasHorizontais == 0) {
        return; // parada
    }

    for (int v = 0; v < casasVerticais; v++) {
        
        for (int h = 0; h < casasHorizontais; h++) {
            printf("Cima, Direita\n");
        }
        // casas horizontais e verticais são iguais

    }

    moverBispoRecursivo(0, 0);
}

void moverBispo(int casas, int passoAtual) {
    if (passoAtual == casas) {
        return; // parada
    }
    // movimento vertical (subida)
    for (int v = 0; v < 1; v++) {  
        // movimento horizontal (direita)
        for (int h = 0; h < 1; h++) {
            printf("Cima, Direita\n");
        }
    }
    // chamada recursiva para próximo passo diagonal
    moverBispo(casas, passoAtual + 1);
}

// Função: movimento do Cavalo
// Cavalo se move duas casas para cima e uma para a direita ("L")
void moverCavalo(int casasCima, int casasDireita) {
    int movimentosVerticais = 0;   // conta os passos para cima feitos
    int movimentosHorizontais = 0; // conta os passos para direita feitos

    for (int i = 0; i < casasCima + 2; i++) {
        if (movimentosVerticais >= casasCima) {
            break;
        }

        if (i == 1) {
            i++; // pular
            continue;
        }

        printf("Cima\n");
        movimentosVerticais++;
    }

    // movimento horizontal (direita)
    int j = 0;
    while (1) {
        if (movimentosHorizontais >= casasDireita) {
            break; // saiu do loop após completar os movimentos
        }
        printf("Direita\n");
        movimentosHorizontais++;
    }
}

int main() {
    // número de casas para cada peça
    const int casasTorre = 5;
    const int casasBispo = 5;
    const int casasRainha = 8;
    const int casasCavaloCima = 2;
    const int casasCavaloDireita = 1;

    // Movimento da Torr
    printf("Movimento da Torre:\n");
    moverTorre(casasTorre);

    printf("\n");

    // Movimento do Bispo
    printf("Movimento do Bispo:\n");
    moverBispo(casasBispo, 0);

    printf("\n");

    // Movimento da Ranha
    printf("Movimento da Rainha:\n");
    moverRainha(casasRainha);

    printf("\n");

    // Movimento do Cavalo
    printf("Movimento do Cavalo:\n");
    moverCavalo(casasCavaloCima, casasCavaloDireita);

    return 0;
}
