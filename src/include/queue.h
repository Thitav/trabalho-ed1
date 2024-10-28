#ifndef QUEUE_H
#define QUEUE_H

#include "block.h"
#include "error.h"
#include "list.h"

typedef List Queue;
typedef ListBlock QueueBlock;

// Inicializa a fila
void queue_init(Queue *queue);
// Adiciona um bloco à fila
QueueBlock *queue_push(Queue *queue, Block *block, Error *error);
// Remove e retorna o bloco do início da fila
Block *queue_pop(Queue *queue);
// Retorna o bloco do início da fila
QueueBlock *queue_first(Queue *queue);
// Retorna o próximo bloco da fila
QueueBlock *queue_next(QueueBlock *queue_block);
// Remove um bloco da fila
void queue_remove(Queue *queue, QueueBlock *queue_block);
// Limpa a fila e libera a memória alocada
void queue_clear(Queue *queue);

#endif
