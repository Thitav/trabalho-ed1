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
  String *name;        // Nome do produto
  String *description; // Descrição do produto
  Stack bids;          // Pilha de lances
};

// Inicializa o produto
void product_init(Product *product, String *name, String *description);
// Adiciona um lance à pilha de lances do produto
bool product_bid_add(Product *product, User *user, float value, Error *error);
// Retorna o bloco do topo da pilha de lances do produto
StackBlock *product_bid_first(Product *product);
// Retorna o próximo bloco da pilha de lances do produto
StackBlock *product_bid_next(StackBlock *stack_block);
// Retorna o lance de um bloco da pilha de lances do produto
Bid *product_bid_get(StackBlock *stack_block);
// Retorna o lance vencedor do produto
Bid *product_end_auction(Product *product);
// Limpa o produto e libera a memória alocada
void product_clear(Product *product);

// Inicializa a lista de produtos
void product_list_init(ProductList *list);
// Adiciona um produto à lista de produtos
void product_list_push(ProductList *list, Product *product, Error *error);
// Remove um produto da lista de produtos
void product_list_remove(ProductList *list, Product *product);
// Retorna o primeiro bloco da lista de produtos
ListBlock *product_list_first(ProductList *list);
// Retorna o próximo bloco da lista de produtos
ListBlock *product_list_next(ListBlock *list_block);
// Retorna o produto de um bloco da lista de produtos
Product *product_list_get(ListBlock *list_block);
// Retorna o produto com o nome especificado ou NULL se não existir
Product *product_list_find(ProductList *list, char *name);
// Limpa a lista de produtos e libera a memória alocada
void product_list_clear(ProductList *list);

#endif
