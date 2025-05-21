#include <stdio.h>
#include <string.h>

struct Carta {
    char nomePais[100];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidade;
};

// Função para obter valores
float getValor(struct Carta c, int opcao) {
    switch(opcao) {
        case 1: return (float)c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return (float)c.pontosTuristicos;
        case 5: return c.densidade;
        default: return 0;
    }
}

// Função para exibição do nome
const char* getNomeAtributo(int opcao) {
    switch(opcao) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        default: return "Desconhecido";
    }
}

int main() {
    struct Carta carta1 = {"Brasil", 203000000, 8515767.0, 2500.0, 100};
    struct Carta carta2 = {"Canadá", 39000000, 9984670.0, 2200.0, 120};

    carta1.densidade = carta1.populacao / carta1.area;
    carta2.densidade = carta2.populacao / carta2.area;

    int atributo1, atributo2;

    printf("===== SUPER TRUNFO FINAL =====\n");
    printf("Escolha o primeiro atributo para comparação:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Demográfica\n");
    printf("Opção: ");
    scanf("%d", &atributo1);

    if (atributo1 < 1 || atributo1 > 5) {
        printf("Opção inválida. Encerrando.\n");
        return 1;
    }

    printf("\nEscolha o segundo atributo para comparação (diferente do primeiro):\n");

    for (int i = 1; i <= 5; i++) {
        if (i != atributo1)
            printf("%d - %s\n", i, getNomeAtributo(i));
    }

    printf("Opção: ");
    scanf("%d", &atributo2);

    if (atributo2 < 1 || atributo2 > 5 || atributo2 == atributo1) {
        printf("Opção inválida ou repetida. Encerrando.\n");
        return 1;
    }

    // Obtem os valores dos atributos
    float valor1_c1 = getValor(carta1, atributo1);
    float valor1_c2 = getValor(carta2, atributo1);
    float valor2_c1 = getValor(carta1, atributo2);
    float valor2_c2 = getValor(carta2, atributo2);

    // Comparação para cada atributo
    int vencedor1 = (atributo1 == 5) ? (valor1_c1 < valor1_c2 ? 1 : (valor1_c2 < valor1_c1 ? 2 : 0))
                                     : (valor1_c1 > valor1_c2 ? 1 : (valor1_c2 > valor1_c1 ? 2 : 0));

    int vencedor2 = (atributo2 == 5) ? (valor2_c1 < valor2_c2 ? 1 : (valor2_c2 < valor2_c1 ? 2 : 0))
                                     : (valor2_c1 > valor2_c2 ? 1 : (valor2_c2 > valor2_c1 ? 2 : 0));

    float soma_c1 = valor1_c1 + valor2_c1;
    float soma_c2 = valor1_c2 + valor2_c2;

    int vencedor_final = (soma_c1 > soma_c2) ? 1 : (soma_c2 > soma_c1 ? 2 : 0);

    printf("\n===== RESULTADO =====\n");
    printf("Carta 1 - %s\n", carta1.nomePais);
    printf("  %s: %.2f\n", getNomeAtributo(atributo1), valor1_c1);
    printf("  %s: %.2f\n", getNomeAtributo(atributo2), valor2_c1);
    printf("  Soma: %.2f\n", soma_c1);

    printf("\nCarta 2 - %s\n", carta2.nomePais);
    printf("  %s: %.2f\n", getNomeAtributo(atributo1), valor1_c2);
    printf("  %s: %.2f\n", getNomeAtributo(atributo2), valor2_c2);
    printf("  Soma: %.2f\n", soma_c2);

    printf("\n===== VENCEDOR DA RODADA =====\n");
    if (vencedor_final == 1)
        printf("Carta 1 (%s) venceu!\n", carta1.nomePais);
    else if (vencedor_final == 2)
        printf("Carta 2 (%s) venceu!\n", carta2.nomePais);
    else
        printf("Empate!\n");

    return 0;
}
