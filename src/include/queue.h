#ifndef QUEUE_H
#define QUEUE_H

#include "block.h"
#include "error.h"
#include "list.h"

typedef List Queue;
typedef ListBlock QueueBlock;

void queue_init(Queue *queue);
QueueBlock *queue_push(Queue *queue, Block *block, Error *error);
Block *queue_pop(Queue *queue);
QueueBlock *queue_first(Queue *queue);
QueueBlock *queue_next(QueueBlock *queue_block);
void queue_remove(Queue *queue, QueueBlock *queue_block);
void queue_clear(Queue *queue);

#endif
