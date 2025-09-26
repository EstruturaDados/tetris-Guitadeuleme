# Tetris Stack — Fila de Peças (C)

Simulação da **fila circular de peças futuras** do jogo *Tetris Stack* (ByteBros).
Inclui **enqueue**, **dequeue**, geração automática de peças (`I`, `O`, `T`, `L`) com **ID único**, e **exibição do estado após cada ação**.

## Requisitos
- GCC ou Clang (C99+)
- Linux/macOS/WSL (testado com GCC)

## Compilar e executar
```bash
make        # compila
make run    # compila e executa
# ou, manualmente:
# gcc -std=c99 -O2 -Wall -Wextra -o tetris_stack_fila tetris_stack_fila.c
# ./tetris_stack_fila
```

## Uso
Ao iniciar, a fila é **pré-carregada** com 5 peças. O menu oferece:
- `1` — Jogar peça (**dequeue**)
- `2` — Inserir nova peça (**enqueue**)
- `0` — Sair

A cada ação, o programa exibe a fila no formato:
```
Fila de peças (5/5)
[T 0] [O 1] [L 2] [I 3] [I 4]
```

## Estrutura de dados
- **Fila circular** com capacidade fixa (`CAPACIDADE_FILA = 5`).
- `struct Peca { char nome; int id; }`
- `struct FilaPecas` mantém `frente`, `tras`, `tamanho` e `proximoId`.

## Organização do código
- `inicializarFila` — semente RNG, pré-carrega a fila.
- `gerarPeca` — escolhe tipo aleatório e atribui **id** sequencial.
- `enfileirar` / `desenfileirar` — operações O(1) com aritmética modular.
- `exibirFila` — percorre a janela circular e imprime `[tipo id]`.

## Commits sugeridos
```bash
git add tetris_stack_fila.c Makefile README.md
git commit -m "feat(queue): fila circular de peças (enqueue/dequeue + exibição)"
git push
```

---
Curadoria de TI — ByteBros
