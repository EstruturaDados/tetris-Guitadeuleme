// tetris_stack_fila.c
// Simulação da fila de peças futuras (fila circular) do Tetris Stack
// Compilar:  gcc -std=c99 -O2 -Wall -Wextra -o tetris_stack_fila tetris_stack_fila.c
// Executar:  ./tetris_stack_fila

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CAPACIDADE_FILA 5 // tamanho fixo da fila

typedef struct
{
    char nome; // tipo: 'I', 'O', 'T', 'L'
    int id;    // identificador único
} Peca;

typedef struct
{
    Peca dados[CAPACIDADE_FILA];
    int frente;    // índice do primeiro elemento
    int tras;      // índice da próxima posição livre
    int tamanho;   // quantidade atual
    int proximoId; // contador de IDs
} FilaPecas;

void inicializarFila(FilaPecas *f);
bool filaVazia(const FilaPecas *f);
bool filaCheia(const FilaPecas *f);
Peca gerarPeca(FilaPecas *f);
bool enfileirar(FilaPecas *f, Peca p);
bool desenfileirar(FilaPecas *f, Peca *removida);
void exibirFila(const FilaPecas *f);

void inicializarFila(FilaPecas *f)
{
    f->frente = 0;
    f->tras = 0;
    f->tamanho = 0;
    f->proximoId = 0;
    srand((unsigned)time(NULL));
    for (int i = 0; i < CAPACIDADE_FILA; i++)
    {
        Peca p = gerarPeca(f);
        enfileirar(f, p);
    }
}

bool filaVazia(const FilaPecas *f) { return f->tamanho == 0; }
bool filaCheia(const FilaPecas *f) { return f->tamanho == CAPACIDADE_FILA; }

Peca gerarPeca(FilaPecas *f)
{
    const char tipos[] = {'I', 'O', 'T', 'L'};
    size_t nTipos = sizeof(tipos) / sizeof(tipos[0]);
    char nome = tipos[rand() % nTipos];
    Peca p;
    p.nome = nome;
    p.id = f->proximoId++;
    return p;
}

bool enfileirar(FilaPecas *f, Peca p)
{
    if (filaCheia(f))
        return false;
    f->dados[f->tras] = p;
    f->tras = (f->tras + 1) % CAPACIDADE_FILA;
    f->tamanho++;
    return true;
}

bool desenfileirar(FilaPecas *f, Peca *removida)
{
    if (filaVazia(f))
        return false;
    *removida = f->dados[f->frente];
    f->frente = (f->frente + 1) % CAPACIDADE_FILA;
    f->tamanho--;
    return true;
}

void exibirFila(const FilaPecas *f)
{
    printf("\n==============================\n");
    printf("Fila de peças (%d/%d)\n", f->tamanho, CAPACIDADE_FILA);
    if (filaVazia(f))
    {
        printf("[vazia]\n");
    }
    else
    {
        for (int i = 0; i < f->tamanho; i++)
        {
            int idx = (f->frente + i) % CAPACIDADE_FILA;
            printf("[%c %d]%s", f->dados[idx].nome, f->dados[idx].id,
                   (i == f->tamanho - 1 ? "\n" : " "));
        }
    }
    printf("==============================\n");
}

int main(void)
{
    FilaPecas fila;
    inicializarFila(&fila);
    int opcao;
    do
    {
        exibirFila(&fila);
        printf("Opções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1)
        {
            fprintf(stderr, "Entrada inválida.\n");
            return 1;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        switch (opcao)
        {
        case 1:
        {
            Peca jogada;
            if (desenfileirar(&fila, &jogada))
            {
                printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
            }
            else
            {
                printf("\nNão há peças para jogar (fila vazia).\n");
            }
            break;
        }
        case 2:
        {
            if (filaCheia(&fila))
            {
                printf("\nNão foi possível inserir: fila cheia.\n");
            }
            else
            {
                Peca nova = gerarPeca(&fila);
                enfileirar(&fila, nova);
                printf("\nPeça gerada e inserida: [%c %d]\n", nova.nome, nova.id);
            }
            break;
        }
        case 0:
            printf("\nSaindo...\n");
            break;
        default:
            printf("\nOpção inválida.\n");
        }
        if (opcao != 0)
            exibirFila(&fila);
    } while (opcao != 0);
    return 0;
}
