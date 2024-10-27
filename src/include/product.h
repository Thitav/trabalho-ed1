#ifndef PRODUCT_H
#define PRODUCT_H

#include "error.h"
#include "globals.h"
#include "list.h"
#include "stack.h"
#include "str.h"
#include <stdbool.h>

typedef List ProductList;
typedef struct Product_s Product;

#include "bid.h"
#include "user.h"

struct Product_s
{
  String *name;
  String *description;
  Stack bids;
};

void product_init(Product *product, String *name, String *description);
bool product_bid_add(Product *product, User *user, float value, Error *error);
StackBlock *product_bid_first(Product *product);
StackBlock *product_bid_next(StackBlock *stack_block);
Bid *product_bid_get(StackBlock *stack_block);
Bid *product_end_auction(Product *product);
void product_clear(Product *product);

void product_list_init(ProductList *list);
void product_list_push(ProductList *list, Product *product, Error *error);
void product_list_remove(ProductList *list, Product *product);
ListBlock *product_list_first(ProductList *list);
ListBlock *product_list_next(ListBlock *list_block);
Product *product_list_get(ListBlock *list_block);
Product *product_list_find(ProductList *list, char *name);
void product_list_clear(ProductList *list);

#endif
