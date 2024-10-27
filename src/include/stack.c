#include "stack.h"
#include "block.h"
#include "list.h"

void stack_init(Stack *stack)
{
  list_init(stack);
}

StackBlock *stack_push(Stack *stack, Block *block, Error *error)
{
  return list_push_tail(stack, block, error);
}

Block *stack_pop(Stack *stack)
{
  return list_pop_tail(stack);
}

StackBlock *stack_first(Stack *stack)
{
  return list_tail(stack);
}

StackBlock *stack_next(StackBlock *stack_block)
{
  return list_prev(stack_block);
}

void stack_remove(Stack *stack, StackBlock *stack_block)
{
  list_remove(stack, stack_block);
}

void stack_clear(Stack *stack)
{
  list_clear(stack);
}
