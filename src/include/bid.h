#ifndef BID_H
#define BID_H

#include "error.h"
#include "queue.h"

typedef struct Bid_s Bid;

#include "product.h"
#include "user.h"

struct Bid_s
{
  float value;      // Valor do lance
  Product *product; // Ponteiro para o produto do lance
  Queue users;      // Lista de usuários que deram o lance
};

// Inicializa o lance
void bid_init(Bid *bid, float value, Product *product);
// Adiciona um usuário à lista de usuários que deram o lance
void bid_user_add(Bid *bid, User *user, Error *error);
// Remove um usuário da lista de usuários que deram o lance
void bid_user_remove(Bid *bid, User *user);
// Retorna o primeiro bloco da lista de usuários que deram o lance
QueueBlock *bid_user_first(Bid *bid);
// Retorna o próximo bloco da lista de usuários que deram o lance
QueueBlock *bid_user_next(QueueBlock *queue_block);
// Retorna o usuário de um bloco da lista de usuários
User *bid_user_get(QueueBlock *queue_block);
// Retorna o usuario vencedor do lance
User *bid_end(Bid *bid);
// Limpa o lance e libera a memória alocada
void bid_clear(Bid *bid);

#endif
