#include <stdio.h>

int main () {
char Estado1; // Uma letra de 'A' a 'H' (representando um dos oito estados)
char Código_da_Carta1 [3];
char Nome_da_Cidade1 [20];
int População1;
float Área1;
float PIB1;
int Número_de_Pontos_Turisticos1;

printf ("CARTA 1\n");

    printf("Digite o Estado (uma letra de A a H): \n");
    scanf(" %c" , &Estado1);

    printf("Digite o Código de Carta: \n");
    scanf("%s" , Código_da_Carta1);

    printf("Digite o Nome da Cidade: \n");
    scanf("%s" , Nome_da_Cidade1);

    printf("Digite a População: \n");
    scanf("%d" , &População1);

    printf("Digite a Área: \n");
    scanf("%f" , &Área1);

    printf("Digite o PIB: \n");
    scanf("%f" , &PIB1);

    printf("Digite o Número de Pontos Turísticos: \n");
    scanf("%d" , &Número_de_Pontos_Turisticos1);

    printf("\nCARTA 1\n");
    printf("Estado: %c\n", Estado1);
    printf("Código de Carta: %s\n", Código_da_Carta1);
    printf("Nome da Cidade: %s\n", Nome_da_Cidade1);
    printf("População: %d\n", População1);
    printf("Área: %f\n", Área1);
    printf("PIB: %f\n", PIB1);
    printf("Número de Pontos Turísticos: %d\n", Número_de_Pontos_Turisticos1);

    return 0;

}