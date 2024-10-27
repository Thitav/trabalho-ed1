#ifndef BID_H
#define BID_H

#include "error.h"
#include "queue.h"

typedef struct Bid_s Bid;

#include "product.h"
#include "user.h"

struct Bid_s
{
  float value;
  Product *product;
  Queue users;
};

void bid_init(Bid *bid, float value, Product *product);
void bid_user_add(Bid *bid, User *user, Error *error);
void bid_user_remove(Bid *bid, User *user);
QueueBlock *bid_user_first(Bid *bid);
QueueBlock *bid_user_next(QueueBlock *queue_block);
User *bid_user_get(QueueBlock *queue_block);
User *bid_end(Bid *bid);
void bid_clear(Bid *bid);

#endif
