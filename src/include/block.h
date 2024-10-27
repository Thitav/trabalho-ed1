#ifndef BLOCK_H
#define BLOCK_H

#include "error.h"
#include <stdlib.h>

/**
 * @struct Block
 * @brief Estrutura que representa um bloco de dados.
 *
 * A estrutura Block contém um tamanho e um array que armazena dados genéricos.
 */
typedef struct
{
  size_t size;
  char data[];
} Block;

/**
 * @brief Aloca um bloco de memória.
 *
 * @param size Capacidade do bloco a ser alocado.
 * @param error Ponteiro para armazenar o código de erro, se houver.
 * @return Ponteiro para o bloco alocado ou NULL, caso `size` seja 0 ou em caso de erro.
 */
Block *block_alloc(size_t size, Error *error);

/**
 * @brief Copia dados para um bloco de memória.
 *
 * @param block Ponteiro para o bloco de memória.
 * @param src Ponteiro para os a serem copiados.
 */
void block_copy_from(Block *block, void *src);
/**
 * @brief Libera um bloco de memória.
 *
 * @param block Ponteiro para o bloco a ser liberado.
 */
void block_free(Block *block);

#endif
