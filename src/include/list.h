#ifndef LIST_H
#define LIST_H

#include "block.h"

typedef struct ListBlock
{
  struct ListBlock *next, *prev;
  Block *block;
} ListBlock;

typedef struct
{
  ListBlock *head, *tail;
  unsigned int len;
} List;

void list_init(List *list);
ListBlock *list_push_tail(List *list, Block *block, Error *error);
ListBlock *list_push_head(List *list, Block *block, Error *error);
Block *list_pop_tail(List *list);
Block *list_pop_head(List *list);
ListBlock *list_tail(List *list);
ListBlock *list_head(List *list);
ListBlock *list_next(ListBlock *list_block);
ListBlock *list_prev(ListBlock *list_block);
ListBlock *list_insert_before(List *list, ListBlock *list_block, Block *block, Error *error);
ListBlock *list_insert_after(List *list, ListBlock *list_block, Block *block, Error *error);
void list_remove(List *list, ListBlock *list_block);
void list_clear(List *list);
void list_log(List *list);

#endif
