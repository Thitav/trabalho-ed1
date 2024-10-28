#include "list.h"
#include "block.h"
#include "error.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void list_init(List *list)
{
  list->head = NULL;
  list->tail = NULL;
  list->len = 0;
}

bool list_is_empty(List *list)
{
  return list->tail == NULL || list->head == NULL;
}

ListBlock *list_push_tail(List *list, Block *block, Error *error)
{
  *error = ERROR_SUCCESS;

  ListBlock *list_block = malloc(sizeof(ListBlock));
  if (list_block == NULL)
  {
    *error = ERROR_MALLOC;
    return NULL;
  }

  list_block->block = block;
  list_block->next = NULL;
  list->len++;

  if (list_is_empty(list) == true)
  {
    list->tail = list_block;
    list->head = list_block;
    list_block->prev = NULL;
    return list_block;
  }

  list->tail->next = list_block;
  list_block->prev = list->tail;
  list->tail = list_block;
  return list_block;
}

ListBlock *list_push_head(List *list, Block *block, Error *error)
{
  *error = ERROR_SUCCESS;

  ListBlock *list_block = malloc(sizeof(ListBlock));
  if (list_block == NULL)
  {
    *error = ERROR_MALLOC;
    return NULL;
  }

  list_block->block = block;
  list_block->prev = NULL;
  list->len++;

  if (list_is_empty(list) == true)
  {
    list->tail = list_block;
    list->head = list_block;
    list_block->next = NULL;
    return list_block;
  }

  list->head->prev = list_block;
  list_block->next = list->head;
  list->head = list_block;
  return list_block;
}

Block *list_pop_tail(List *list)
{
  if (list_is_empty(list) == true)
  {
    return NULL;
  }

  ListBlock *list_block = list->tail;
  Block *block = list_block->block;

  list->tail = list_block->prev;
  if (list->tail != NULL)
  {
    list->tail->next = NULL;
  }
  free(list_block);
  list->len--;

  return block;
}

Block *list_pop_head(List *list)
{
  if (list_is_empty(list) == true)
  {
    return NULL;
  }

  ListBlock *list_block = list->head;
  Block *block = list_block->block;

  list->head = list_block->next;
  if (list->head != NULL)
  {
    list->head->prev = NULL;
  }
  free(list_block);
  list->len--;

  return block;
}

ListBlock *list_tail(List *list)
{
  return list->tail;
}

ListBlock *list_head(List *list)
{
  return list->head;
}

ListBlock *list_next(ListBlock *list_block)
{
  return list_block->next;
}

ListBlock *list_prev(ListBlock *list_block)
{
  return list_block->prev;
}

ListBlock *list_insert_before(List *list, ListBlock *list_block, Block *block, Error *error)
{
  *error = ERROR_SUCCESS;

  ListBlock *new_list_block = malloc(sizeof(ListBlock));
  if (list_block == NULL)
  {
    *error = ERROR_MALLOC;
    return NULL;
  }

  new_list_block->block = block;
  list->len++;

  if (list_is_empty(list) == true)
  {
    list->head = new_list_block;
    list->tail = new_list_block;
    new_list_block->next = NULL;
    new_list_block->prev = NULL;
    return new_list_block;
  }

  if (list_block == NULL)
  {
    new_list_block->next = list->head;
    new_list_block->prev = NULL;
    list->head->prev = new_list_block;
    list->head = new_list_block;
  }
  else
  {
    ListBlock *prev = list_block->prev;
    new_list_block->next = list_block;
    new_list_block->prev = prev;
    list_block->prev = new_list_block;
    if (prev == NULL)
    {
      list->head = new_list_block;
    }
    else
    {
      prev->next = new_list_block;
    }
  }
  return new_list_block;
}

ListBlock *list_insert_after(List *list, ListBlock *list_block, Block *block, Error *error)
{
  *error = ERROR_SUCCESS;

  ListBlock *new_list_block = malloc(sizeof(ListBlock));
  if (list_block == NULL)
  {
    *error = ERROR_MALLOC;
    return NULL;
  }

  list_block->block = block;
  list->len++;

  if (list_is_empty(list) == true)
  {
    list->head = new_list_block;
    list->tail = new_list_block;
    new_list_block->next = NULL;
    new_list_block->prev = NULL;
    return new_list_block;
  }

  if (list_block == NULL)
  {
    new_list_block->next = NULL;
    new_list_block->prev = list->tail;
    list->tail->next = new_list_block;
    list->tail = new_list_block;
  }
  else
  {
    ListBlock *next = list_block->next;
    new_list_block->next = next;
    new_list_block->prev = list_block;
    list_block->next = new_list_block;
    if (next == NULL)
    {
      list->tail = new_list_block;
    }
    else
    {
      next->prev = new_list_block;
    }
  }
  return new_list_block;
}

void list_remove(List *list, ListBlock *list_block)
{
  ListBlock *prev = list_block->prev;
  ListBlock *next = list_block->next;

  if (prev != NULL)
  {
    prev->next = next;
  }
  if (next != NULL)
  {
    next->prev = prev;
  }

  if (list->head == list_block)
  {
    list->head = next;
  }
  if (list->tail == list_block)
  {
    list->tail = prev;
  }

  list->len--;

  block_free(list_block->block);
  free(list_block);
}

void list_clear(List *list)
{
  ListBlock *list_block = list->head;
  while (list_block != NULL)
  {
    ListBlock *next = list_block->next;
    block_free(list_block->block);
    free(list_block);
    list_block = next;
  }

  list->head = NULL;
  list->tail = NULL;
  list->len = 0;
}
