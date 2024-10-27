#include "bid.h"
#include "error.h"
#include "queue.h"
#include "user.h"

void bid_init(Bid *bid, float value, Product *product)
{
  bid->value = value;
  bid->product = product;
  queue_init(&bid->users);
}

void bid_user_add(Bid *bid, User *user, Error *error)
{
  *error = ERROR_SUCCESS;

  Block *block = block_alloc(sizeof(User *), error);
  if (*error != ERROR_SUCCESS)
  {
    return;
  }

  queue_push(&bid->users, block, error);
  if (*error != ERROR_SUCCESS)
  {
    block_free(block);
    return;
  }

  block_copy_from(block, &user);
}

void bid_user_remove(Bid *bid, User *user)
{
  for (QueueBlock *queue_block = bid_user_first(bid); queue_block != NULL; queue_block = bid_user_next(queue_block))
  {
    if (bid_user_get(queue_block) == user)
    {
      queue_remove(&bid->users, queue_block);
      return;
    }
  }
}

QueueBlock *bid_user_first(Bid *bid)
{
  return queue_first(&bid->users);
}

QueueBlock *bid_user_next(QueueBlock *queue_block)
{
  return queue_next(queue_block);
}

User *bid_user_get(QueueBlock *queue_block)
{
  return *(User **)queue_block->block->data;
}

User *bid_end(Bid *bid)
{
  return bid_user_get(bid_user_first(bid));
}

void bid_clear(Bid *bid)
{
  for (QueueBlock *queue_block = bid_user_first(bid); queue_block != NULL; queue_block = bid_user_next(queue_block))
  {
    user_bid_remove(bid_user_get(queue_block), bid);
  }
  queue_clear(&bid->users);
}
