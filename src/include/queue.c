#include "queue.h"
#include "block.h"
#include "error.h"
#include "list.h"

void queue_init(Queue *queue)
{
  list_init(queue);
}

QueueBlock *queue_push(Queue *queue, Block *block, Error *error)
{
  return list_push_tail(queue, block, error);
}

Block *queue_pop(Queue *queue)
{
  return list_pop_head(queue);
}

QueueBlock *queue_first(Queue *queue)
{
  return list_head(queue);
}

QueueBlock *queue_next(QueueBlock *queue_block)
{
  return list_next(queue_block);
}

void queue_remove(Queue *queue, QueueBlock *queue_block)
{
  list_remove(queue, queue_block);
}

void queue_clear(Queue *queue)
{
  list_clear(queue);
}
