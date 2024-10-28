#ifndef BLOCK_H
#define BLOCK_H

#include "error.h"
#include <stdlib.h>

typedef struct
{
  size_t size; // Capacidade de armazenamento do bloco
  char data[]; // Dados do bloco
} Block;

// Aloca um bloco de memória com a estrutura Block
Block *block_alloc(size_t size, Error *error);
// Copia os dados de uma origem para o bloco, respeitando sua capacidade de armazenamento
void block_copy_from(Block *block, void *src);
// Libera a memória alocada para o bloco
void block_free(Block *block);

#endif
