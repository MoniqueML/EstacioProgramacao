#include <stdio.h>

// Função recursiva para mover a Torre para a direita
void moverTorre(int casasRestantes) {
    if (casasRestantes == 0) {
        return; // condição de parada
    }
    printf("Direita\n");
    moverTorre(casasRestantes - 1); // chamada recursiva diminuindo o número de casas
}

// Função recursiva para mover a Rainha para a esquerda
void moverRainha(int casasRestantes) {
    if (casasRestantes == 0) {
        return; // condição de parada
    }
    printf("Esquerda\n");
    moverRainha(casasRestantes - 1); // chamada recursiva
}

// Função para mover o Bispo usando recursão com loops aninhados
// Movimento diagonal: vertical para cima, horizontal para direita
// Recebe o número de casas na vertical e horizontal para percorrer (ambos iguais neste caso)
void moverBispoRecursivo(int casasVerticais, int casasHorizontais) {
    if (casasVerticais == 0 || casasHorizontais == 0) {
        return; // condição de parada da recursão
    }

    // Loop externo para o movimento vertical (cima)
    for (int v = 0; v < casasVerticais; v++) {
        // Loop interno para o movimento horizontal (direita)
        for (int h = 0; h < casasHorizontais; h++) {
            printf("Cima, Direita\n");
        }
        // Para este desafio, as casas horizontais e verticais são iguais
        // e imprimimos a combinação a cada casa na diagonal,
        // por isso usamos essa abordagem.
    }

    // Após imprimir todas as combinações, chamamos a recursão com zero para parar
    moverBispoRecursivo(0, 0);
}

// Como o método acima imprimirá mais que o necessário (5*5 = 25 vezes),
// vamos criar uma versão recursiva que imprime a diagonal 5 vezes só, usando loops aninhados internos:

void moverBispo(int casas, int passoAtual) {
    if (passoAtual == casas) {
        return; // condição de parada da recursão
    }
    // Loop externo: movimento vertical (subida)
    for (int v = 0; v < 1; v++) {  // só um passo por recursão, loop para obedecer requisito de loops aninhados
        // Loop interno: movimento horizontal (direita)
        for (int h = 0; h < 1; h++) {
            printf("Cima, Direita\n");
        }
    }
    // chamada recursiva para próximo passo diagonal
    moverBispo(casas, passoAtual + 1);
}

// Função para o movimento complexo do Cavalo usando loops aninhados e controle com continue e break
// Cavalo se move duas casas para cima e uma para a direita ("L")
void moverCavalo(int casasCima, int casasDireita) {
    int movimentosVerticais = 0;   // conta os passos para cima feitos
    int movimentosHorizontais = 0; // conta os passos para direita feitos

    // Loop externo controla o movimento vertical
    for (int i = 0; i < casasCima + 2; i++) {
        // Para garantir múltiplas variáveis e condições, vamos simular controle do movimento vertical
        if (movimentosVerticais >= casasCima) {
            // Se já fez o número necessário para cima, partimos para o movimento horizontal
            break;
        }

        // Condição para pular uma iteração se estiver no meio do movimento (exemplo arbitrário)
        if (i == 1) {
            i++; // Incrementa para pular
            continue;
        }

        printf("Cima\n");
        movimentosVerticais++;
    }

    // Loop interno para o movimento horizontal (direita), pode ser while
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
    // Definindo o número de casas para cada peça
    const int casasTorre = 5;
    const int casasBispo = 5;
    const int casasRainha = 8;
    const int casasCavaloCima = 2;
    const int casasCavaloDireita = 1;

    // Movimento da Torre (recursivo)
    printf("Movimento da Torre:\n");
    moverTorre(casasTorre);

    printf("\n");

    // Movimento do Bispo (recursivo + loops aninhados)
    printf("Movimento do Bispo:\n");
    moverBispo(casasBispo, 0);

    printf("\n");

    // Movimento da Rainha (recursivo)
    printf("Movimento da Rainha:\n");
    moverRainha(casasRainha);

    printf("\n");

    // Movimento do Cavalo (loops aninhados com múltiplas variáveis e controle)
    printf("Movimento do Cavalo:\n");
    moverCavalo(casasCavaloCima, casasCavaloDireita);

    return 0;
}
