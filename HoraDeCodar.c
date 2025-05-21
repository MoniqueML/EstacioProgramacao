#include <stdio.h>

int main() {
    int Idade, Matricula;
    float Altura;
    char Nome [50];

    printf("Digite sua Idade: \n");
    scanf("%d" , &Idade);

    printf("Digite sua Altura: \n");
    scanf("%f" , &Altura);

    printf("Digite seu Nome: \n");
    scanf("%s" , &Nome);

    printf("Digite sua Matricula: \n");
    scanf("%d" , &Matricula);

    printf("Nome do aluno: %s - Matricula: %d\n", Nome, Matricula);
    printf("Idade: %d - Altura: %f", Idade, Altura);
    
    return 0;
}