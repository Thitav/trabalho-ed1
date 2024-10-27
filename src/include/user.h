#ifndef USER_H
#define USER_H

#include "error.h"
#include "globals.h"
#include "list.h"
#include "str.h"

typedef List UserList;
typedef struct User_s User;

#include "bid.h"

struct User_s
{
  String *name;
  List bids;
};

void user_init(User *user, String *name);
void user_bid_add(User *user, Bid *bid, Error *error);
void user_bid_remove(User *user, Bid *bid);
ListBlock *user_bid_first(User *user);
ListBlock *user_bid_next(ListBlock *list_block);
Bid *user_bid_get(ListBlock *list_block);
void user_clear(User *user);

void user_list_init(UserList *list);
User *user_list_push(UserList *list, User *user, Error *error);
ListBlock *user_list_first(UserList *list);
ListBlock *user_list_next(ListBlock *list_block);
User *user_list_get(ListBlock *list_block);
User *user_list_find(UserList *list, char *name);
void user_list_clear(UserList *list);

#endif
