#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// ---------------------
// Estrutura da peça
// ---------------------
typedef struct {
    char tipo;   // A, B, C ou D
    int id;      // identificador único
} Peca;

// ---------------------
// Configurações
// ---------------------
#define TAM_FILA 5
#define TAM_PILHA 3

// ---------------------
// Variáveis globais
// ---------------------
Peca fila[TAM_FILA];
int inicio = 0;
int fim = 0;
int qtdFila = 0;

Peca pilha[TAM_PILHA];
int topo = -1;

int ultimoID = 1;

// ---------------------
// Função para gerar peça aleatória
// ---------------------
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'A','B','C','D'};
    p.tipo = tipos[rand() % 4];
    p.id = ultimoID++;
    return p;
}

// ---------------------
// FILA (Nível Novato)
// ---------------------
bool filaCheia() {
    return qtdFila == TAM_FILA;
}

bool filaVazia() {
    return qtdFila == 0;
}

void enqueue(Peca p) {
    if (!filaCheia()) {
        fila[fim] = p;
        fim = (fim + 1) % TAM_FILA;
        qtdFila++;
    }
}

Peca dequeue() {
    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    qtdFila--;
    return removida;
}

void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }
}

// ---------------------
// PILHA (Nível Aventureiro)
// ---------------------
bool pilhaCheia() {
    return topo == TAM_PILHA - 1;
}

bool pilhaVazia() {
    return topo == -1;
}

void push(Peca p) {
    if (!pilhaCheia()) {
        pilha[++topo] = p;
    }
}

Peca pop() {
    return pilha[topo--];
}

// ---------------------
// Mostrar estruturas
// ---------------------
void mostrarFila() {
    printf("\n--- FILA (5 peças) ---\n");
    if (filaVazia()) {
        printf("Fila vazia.\n");
        return;
    }

    int idx = inicio;
    for (int i = 0; i < qtdFila; i++) {
        printf("[%d] Tipo: %c | ID: %d\n", i+1, fila[idx].tipo, fila[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
}

void mostrarPilha() {
    printf("\n--- PILHA (Reserva - max 3) ---\n");
    if (pilhaVazia()) {
        printf("Pilha vazia.\n");
        return;
    }

    for (int i = topo; i >= 0; i--) {
        printf("Topo -> Tipo: %c | ID: %d\n", pilha[i].tipo, pilha[i].id);
    }
}

// ---------------------
// Nível Mestre – Trocas avançadas
// ---------------------
void trocarFrenteComTopo() {
    if (filaVazia()) {
        printf("\nNão dá para trocar, fila vazia.\n");
        return;
    }
    if (pilhaVazia()) {
        printf("\nNão dá para trocar, pilha vazia.\n");
        return;
    }

    Peca temp = fila[inicio];
    fila[inicio] = pilha[topo];
    pilha[topo] = temp;

    printf("\nPeças trocadas com sucesso!\n");
}

void trocarTresComTres() {
    if (qtdFila < 3) {
        printf("\nFila não tem 3 peças para trocar.\n");
        return;
    }
    if (topo < 2) {
        printf("\nPilha não tem 3 peças para trocar.\n");
        return;
    }

    // Troca 3 primeiras da fila com os 3 da pilha
    for (int i = 0; i < 3; i++) {
        int idxFila = (inicio + i) % TAM_FILA;
        Peca temp = fila[idxFila];
        fila[idxFila] = pilha[topo - i];
        pilha[topo - i] = temp;
    }

    printf("\nAs 3 primeiras peças da fila foram trocadas com as 3 da pilha!\n");
}

// ---------------------
// Programa principal
// ---------------------
int main() {
    srand(time(NULL));

    inicializarFila();

    int op;

    do {
        printf("\n\n===== MENU TETRIS STACK =====\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Reservar peça (fila -> pilha)\n");
        printf("3 - Usar peça reservada (pilha -> usado)\n");
        printf("4 - Trocar peça da frente com topo da pilha\n");
        printf("5 - Trocar 3 da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch(op) {

            case 1: {
                if (filaVazia()) {
                    printf("\nNão há peça para jogar.\n");
                } else {
                    Peca jogada = dequeue();
                    printf("\nPeça jogada -> Tipo: %c | ID: %d\n", jogada.tipo, jogada.id);
                    enqueue(gerarPeca()); // mantém fila cheia
                }
                break;
            }

            case 2: {
                if (filaVazia()) {
                    printf("\nFila vazia, nada para reservar.\n");
                } else if (pilhaCheia()) {
                    printf("\nPilha cheia, não dá para reservar.\n");
                } else {
                    Peca reservada = dequeue();
                    push(reservada);
                    printf("\nPeça reservada -> Tipo: %c | ID: %d\n", reservada.tipo, reservada.id);
                    enqueue(gerarPeca());
                }
                break;
            }

            case 3: {
                if (pilhaVazia()) {
                    printf("\nPilha vazia, nada reservado para usar.\n");
                } else {
                    Peca usada = pop();
                    printf("\nPeça usada da reserva -> Tipo: %c | ID: %d\n", usada.tipo, usada.id);
                }
                break;
            }

            case 4:
                trocarFrenteComTopo();
                break;

            case 5:
                trocarTresComTres();
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida.\n");
        }

        mostrarFila();
        mostrarPilha();

    } while(op != 0);

    return 0;
}
