#include "user.h"
#include "bid.h"
#include "block.h"
#include "str.h"
#include <string.h>

void user_init(User *user, String *name)
{
  user->name = name;
  list_init(&user->bids);
}

void user_bid_add(User *user, Bid *bid, Error *error)
{
  *error = ERROR_SUCCESS;

  Block *block = block_alloc(sizeof(Bid *), error);
  if (*error != ERROR_SUCCESS)
  {
    return;
  }

  block_copy_from(block, &bid);
  list_push_tail(&user->bids, block, error);
}

void user_bid_remove(User *user, Bid *bid)
{
  for (ListBlock *list_block = user_bid_first(user); list_block != NULL; list_block = user_bid_next(list_block))
  {
    if (user_bid_get(list_block) == bid)
    {
      list_remove(&user->bids, list_block);
      return;
    }
  }
}

ListBlock *user_bid_first(User *user)
{
  return list_head(&user->bids);
}

ListBlock *user_bid_next(ListBlock *list_block)
{
  return list_next(list_block);
}

Bid *user_bid_get(ListBlock *list_block)
{
  return *(Bid **)list_block->block->data;
}

void user_clear(User *user)
{
  for (ListBlock *list_block = user_bid_first(user); list_block != NULL; list_block = user_bid_next(list_block))
  {
    bid_user_remove(user_bid_get(list_block), user);
  }
  list_clear(&user->bids);
  string_free(user->name);
}

void user_list_init(UserList *list)
{
  list_init(list);
}

User *user_list_push(UserList *list, User *user, Error *error)
{
  *error = ERROR_SUCCESS;

  if (user_list_find(list, string_cstr(user->name)) != NULL)
  {
    return NULL;
  }

  Block *block = block_alloc(sizeof(User), error);
  if (*error != ERROR_SUCCESS)
  {
    return NULL;
  }

  list_push_tail(list, block, error);
  if (*error != ERROR_SUCCESS)
  {
    block_free(block);
    return NULL;
  }

  block_copy_from(block, user);
  return (User *)block->data;
}

ListBlock *user_list_first(UserList *list)
{
  return list_head(list);
}

ListBlock *user_list_next(ListBlock *list_block)
{
  return list_next(list_block);
}

User *user_list_get(ListBlock *list_block)
{
  return (User *)list_block->block->data;
}

User *user_list_find(UserList *list, char *name)
{
  for (ListBlock *list_block = user_list_first(list); list_block != NULL; list_block = user_list_next(list_block))
  {
    User *user = user_list_get(list_block);
    if (string_cmp_cstr(user->name, name) == 0)
    {
      return user;
    }
  }
  return NULL;
}

void user_list_clear(UserList *list)
{
  for (ListBlock *list_block = user_list_first(list); list_block != NULL; list_block = user_list_next(list_block))
  {
    user_clear(user_list_get(list_block));
  }
  list_clear(list);
}
