#include "product.h"
#include "bid.h"
#include "block.h"
#include "error.h"
#include "globals.h"
#include "stack.h"
#include "str.h"
#include "user.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void product_init(Product *product, String *name, String *description)
{
  product->name = name;
  product->description = description;
  stack_init(&product->bids);
}

bool product_bid_add(Product *product, User *user, float value, Error *error)
{
  *error = ERROR_SUCCESS;

  ListBlock *top_block = stack_first(&product->bids);
  Bid *top_bid = top_block == NULL ? NULL : product_bid_get(top_block);

  if (top_bid == NULL || top_bid->value < value)
  {
    Block *block = block_alloc(sizeof(Bid), error);
    if (*error != ERROR_SUCCESS)
    {
      return false;
    }

    Bid *bid = (Bid *)block->data;
    bid_init(bid, value, product);
    stack_push(&product->bids, block, error);
    if (*error != ERROR_SUCCESS)
    {
      block_free(block);
      return false;
    }

    bid_user_add(bid, user, error);
    if (*error != ERROR_SUCCESS)
    {
      block_free(stack_pop(&product->bids));
      return false;
    }

    user_bid_add(user, bid, error);
    if (*error != ERROR_SUCCESS)
    {
      bid_user_remove(bid, user);
      block_free(stack_pop(&product->bids));
      return false;
    }

    return true;
  }
  else if (top_bid->value == value)
  {
    bid_user_add(top_bid, user, error);
    if (*error != ERROR_SUCCESS)
    {
      return false;
    }

    user_bid_add(user, top_bid, error);
    if (*error != ERROR_SUCCESS)
    {
      return false;
    }

    return true;
  }

  return false;
}

StackBlock *product_bid_first(Product *product)
{
  return stack_first(&product->bids);
}

StackBlock *product_bid_next(StackBlock *stack_block)
{
  return stack_next(stack_block);
}

Bid *product_bid_get(StackBlock *stack_block)
{
  return (Bid *)stack_block->block->data;
}

Bid *product_end_auction(Product *product)
{
  ListBlock *stack_block = product_bid_first(product);
  if (stack_block == NULL)
  {
    return NULL;
  }

  return product_bid_get(stack_block);
}

void product_clear(Product *product)
{
  for (StackBlock *stack_block = product_bid_first(product); stack_block != NULL; stack_block = product_bid_next(stack_block))
  {
    bid_clear(product_bid_get(stack_block));
  }
  stack_clear(&product->bids);
  string_free(product->name);
  string_free(product->description);
}

void product_list_init(ProductList *list)
{
  list_init(list);
}

void product_list_push(ProductList *list, Product *product, Error *error)
{
  *error = ERROR_SUCCESS;

  Block *block = block_alloc(sizeof(Product), error);
  if (*error != ERROR_SUCCESS)
  {
    return;
  }

  block_copy_from(block, product);

  for (ListBlock *list_block = product_list_first(list); list_block != NULL; list_block = product_list_next(list_block))
  {
    Product *current_product = product_list_get(list_block);
    if (string_cmp(current_product->name, product->name) >= 0)
    {
      list_insert_before(list, list_block, block, error);
      if (*error != ERROR_SUCCESS)
      {
        block_free(block);
      }
      return;
    }
  }

  list_push_tail(list, block, error);
  if (*error != ERROR_SUCCESS)
  {
    block_free(block);
  }
}

void product_list_remove(ProductList *list, Product *product)
{
  for (ListBlock *list_block = product_list_first(list); list_block != NULL; list_block = product_list_next(list_block))
  {
    if (product_list_get(list_block) == product)
    {
      list_remove(list, list_block);
      return;
    }
  }
}

ListBlock *product_list_first(ProductList *list)
{
  return list_head(list);
}

ListBlock *product_list_next(ListBlock *list_block)
{
  return list_next(list_block);
}

Product *product_list_get(ListBlock *list_block)
{
  return (Product *)list_block->block->data;
}

Product *product_list_find(ProductList *list, char *name)
{
  for (ListBlock *list_block = product_list_first(list); list_block != NULL; list_block = product_list_next(list_block))
  {
    Product *product = product_list_get(list_block);
    if (string_cmp_cstr(product->name, name) == 0)
    {
      return product;
    }
  }
  return NULL;
}

void product_list_clear(ProductList *list)
{
  for (ListBlock *list_block = product_list_first(list); list_block != NULL; list_block = product_list_next(list_block))
  {
    product_clear(product_list_get(list_block));
  }
  list_clear(list);
}
