#ifndef STACK_H
#define STACK_H

#include "block.h"
#include "error.h"
#include "list.h"

typedef List Stack;
typedef ListBlock StackBlock;

// Inicializa a pilha
void stack_init(Stack *Stack);
// Adiciona um bloco à pilha
StackBlock *stack_push(Stack *Stack, Block *block, Error *error);
// Remove e retorna o bloco do topo da pilha
Block *stack_pop(Stack *Stack);
// Retorna o bloco do topo da pilha
StackBlock *stack_first(Stack *stack);
// Retorna o próximo bloco da pilha
StackBlock *stack_next(StackBlock *stack_block);
// Remove um bloco da pilha
void stack_remove(Stack *stack, StackBlock *stack_block);
// Limpa a pilha e libera a memória alocada
void stack_clear(Stack *stack);

#endif
