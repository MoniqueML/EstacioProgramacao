#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_LEN 64
#define PISTA_LEN 256
#define HASH_SIZE 101

typedef struct Sala {
    char nome[NOME_LEN];
    char pista[PISTA_LEN];
    int pistaColetada;
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

typedef struct PistaNode {
    char texto[PISTA_LEN];
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;

typedef struct HashNode {
    char chave[PISTA_LEN];
    char suspeito[NOME_LEN];
    struct HashNode *prox;
} HashNode;

typedef struct {
    HashNode *buckets[HASH_SIZE];
} HashTable;

Sala* criarSala(const char nome[], const char pista[]) {
    Sala *nova = malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->pistaColetada = 0;
    nova->esquerda = nova->direita = NULL;
    return nova;
}

PistaNode* inserirPista(PistaNode *root, const char texto[]) {
    if (root == NULL) {
        PistaNode *n = malloc(sizeof(PistaNode));
        strcpy(n->texto, texto);
        n->esq = n->dir = NULL;
        return n;
    }
    int cmp = strcmp(texto, root->texto);
    if (cmp < 0) root->esq = inserirPista(root->esq, texto);
    else if (cmp > 0) root->dir = inserirPista(root->dir, texto);
    return root;
}

void exibirPistas(PistaNode *root) {
    if (!root) return;
    exibirPistas(root->esq);
    printf("- %s\n", root->texto);
    exibirPistas(root->dir);
}

unsigned long hashStr(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

HashTable* criarHash() {
    HashTable *h = malloc(sizeof(HashTable));
    for (int i = 0; i < HASH_SIZE; i++) h->buckets[i] = NULL;
    return h;
}

void inserirNaHash(HashTable *h, const char chave[], const char suspeito[]) {
    unsigned long hv = hashStr(chave) % HASH_SIZE;
    HashNode *n = malloc(sizeof(HashNode));
    strcpy(n->chave, chave);
    strcpy(n->suspeito, suspeito);
    n->prox = h->buckets[hv];
    h->buckets[hv] = n;
}

char* encontrarSuspeito(HashTable *h, const char chave[]) {
    unsigned long hv = hashStr(chave) % HASH_SIZE;
    for (HashNode *cur = h->buckets[hv]; cur; cur = cur->prox)
        if (strcmp(cur->chave, chave) == 0) return cur->suspeito;
    return NULL;
}

int contarPistasParaSuspeito(PistaNode *root, HashTable *h, const char suspeito[]) {
    if (!root) return 0;
    int cont = contarPistasParaSuspeito(root->esq, h, suspeito);
    char *s = encontrarSuspeito(h, root->texto);
    if (s && strcmp(s, suspeito) == 0) cont++;
    cont += contarPistasParaSuspeito(root->dir, h, suspeito);
    return cont;
}

void explorarSalas(Sala *atual, PistaNode **pistas, HashTable *h) {
    char op[8];
    while (atual) {
        printf("\nVocê está no: %s\n", atual->nome);
        if (strlen(atual->pista) > 0 && !atual->pistaColetada) {
            printf("Pista encontrada: %s\n", atual->pista);
            *pistas = inserirPista(*pistas, atual->pista);
            atual->pistaColetada = 1;
        }
        if (!atual->esquerda && !atual->direita) {
            printf("Fim dos caminhos. Digite 's' para sair: ");
            fgets(op, sizeof(op), stdin);
            if (op[0] == 's' || op[0] == 'S') break;
        }
        printf("Ir (e) esquerda, (d) direita ou (s) sair: ");
        fgets(op, sizeof(op), stdin);
        if (op[0] == 'e' || op[0] == 'E') atual = atual->esquerda;
        else if (op[0] == 'd' || op[0] == 'D') atual = atual->direita;
        else if (op[0] == 's' || op[0] == 'S') break;
    }
}

int main() {
    Sala *hall = criarSala("Hall de Entrada", "Pegadas molhadas na porta");
    Sala *salaEstar = criarSala("Sala de Estar", "Marca de batom no copo");
    Sala *cozinha = criarSala("Cozinha", "Receita rasgada com iniciais");
    Sala *biblioteca = criarSala("Biblioteca", "Página arrancada sobre herança");
    Sala *jardim = criarSala("Jardim", "Botas com barro raro");
    Sala *porao = criarSala("Porão", "Correntes e pano com cheiro forte");
    Sala *salaSecreta = criarSala("Sala Secreta", "Bilhete: 'Encontro meia-noite'");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->esquerda = porao;
    cozinha->direita = salaSecreta;

    HashTable *hash = criarHash();
    inserirNaHash(hash, "Pegadas molhadas na porta", "Sr. Silva");
    inserirNaHash(hash, "Marca de batom no copo", "Sra. Oliveira");
    inserirNaHash(hash, "Receita rasgada com iniciais", "Sr. Silva");
    inserirNaHash(hash, "Página arrancada sobre herança", "Dr. Castro");
    inserirNaHash(hash, "Botas com barro raro", "Sr. Pereira");
    inserirNaHash(hash, "Correntes e pano com cheiro forte", "Dr. Castro");
    inserirNaHash(hash, "Bilhete: 'Encontro meia-noite'", "Sra. Oliveira");

    PistaNode *pistas = NULL;
    explorarSalas(hall, &pistas, hash);

    printf("\nPistas coletadas:\n");
    if (pistas) exibirPistas(pistas);
    else printf("Nenhuma pista coletada.\n");

    char acusado[NOME_LEN];
    printf("\nQuem você acusa? ");
    fgets(acusado, sizeof(acusado), stdin);
    acusado[strcspn(acusado, "\n")] = 0;

    int total = contarPistasParaSuspeito(pistas, hash, acusado);
    if (total >= 2)
        printf("Acusação sustentada! (%d pistas apontam para %s)\n", total, acusado);
    else
        printf("Acusação não sustentada (%d pistas).\n", total);

    printf("\nFim do jogo.\n");
    return 0;
}
