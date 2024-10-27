#ifndef STACK_H
#define STACK_H

#include "block.h"
#include "error.h"
#include "list.h"

typedef List Stack;
typedef ListBlock StackBlock;

void stack_init(Stack *Stack);
StackBlock *stack_push(Stack *Stack, Block *block, Error *error);
Block *stack_pop(Stack *Stack);
StackBlock *stack_first(Stack *stack);
StackBlock *stack_next(StackBlock *stack_block);
void stack_remove(Stack *stack, StackBlock *stack_block);
void stack_clear(Stack *stack);

#endif
