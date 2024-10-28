#ifndef LIST_H
#define LIST_H

#include "block.h"
#include <stdlib.h>

typedef struct ListBlock
{
  struct ListBlock *next, *prev; // Ponteiros para o próximo e anterior blocos
  Block *block;                  // Ponteiro para o bloco de dados
} ListBlock;

typedef struct
{
  ListBlock *head, *tail; // Ponteiros para os primeiro e último blocos
  size_t len;             // Número de blocos da lista
} List;

// Inicializa a lista
void list_init(List *list);
// Adiciona um bloco ao final da lista
ListBlock *list_push_tail(List *list, Block *block, Error *error);
// Adiciona um bloco ao início da lista
ListBlock *list_push_head(List *list, Block *block, Error *error);
// Remove e retorna o bloco do final da lista
Block *list_pop_tail(List *list);
// Remove e retorna o bloco do início da lista
Block *list_pop_head(List *list);
// Retorna o último bloco da lista
ListBlock *list_tail(List *list);
// Retorna o primeiro bloco da lista
ListBlock *list_head(List *list);
// Retorna o próximo bloco da lista
ListBlock *list_next(ListBlock *list_block);
// Retorna o bloco anterior da lista
ListBlock *list_prev(ListBlock *list_block);
// Insere um bloco antes de outro bloco na lista
ListBlock *list_insert_before(List *list, ListBlock *list_block, Block *block, Error *error);
// Insere um bloco depois de outro bloco na lista
ListBlock *list_insert_after(List *list, ListBlock *list_block, Block *block, Error *error);
// Remove um bloco da lista
void list_remove(List *list, ListBlock *list_block);
// Limpa a lista e libera a memória alocada
void list_clear(List *list);

#endif
