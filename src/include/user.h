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
  String *name; // Nome do usuário
  List bids;    // Lista de lances dados pelo usuário
};

// Inicializa o usuário
void user_init(User *user, String *name);
// Adiciona um lance à lista de lances do usuário
void user_bid_add(User *user, Bid *bid, Error *error);
// Remove um lance da lista de lances do usuário
void user_bid_remove(User *user, Bid *bid);
// Retorna o primeiro bloco da lista de lances do usuário
ListBlock *user_bid_first(User *user);
// Retorna o próximo bloco da lista de lances do usuário
ListBlock *user_bid_next(ListBlock *list_block);
// Retorna o lance de um bloco da lista de lances do usuário
Bid *user_bid_get(ListBlock *list_block);
// Limpa o usuário e libera a memória alocada
void user_clear(User *user);

// Inicializa a lista de usuários
void user_list_init(UserList *list);
// Adiciona um usuário à lista de usuários
User *user_list_push(UserList *list, User *user, Error *error);
// Retorna o primeiro bloco da lista de usuários
ListBlock *user_list_first(UserList *list);
// Retorna o próximo bloco da lista de usuários
ListBlock *user_list_next(ListBlock *list_block);
// Retorna o usuário de um bloco da lista de usuários
User *user_list_get(ListBlock *list_block);
// Retorna o usuário com o nome especificado ou NULL se não existir
User *user_list_find(UserList *list, char *name);
// Limpa a lista de usuários e libera a memória alocada
void user_list_clear(UserList *list);

#endif
