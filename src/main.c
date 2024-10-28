#include "bid.h"
#include "error.h"
#include "globals.h"
#include "product.h"
#include "str.h"
#include "user.h"
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cadastra um produto
void products_add(ProductList *products)
{
  Error error;
  Product product;
  String *name, *description;
  char buff[BASE_STRING_SIZE] = {0};

  printf("\tEntre com o nome do produto: ");
  if (fgets(buff, sizeof(buff), stdin) == NULL)
  {
    fputs(error_message(ERROR_INPUT), stderr);
    return;
  }
  buff[strcspn(buff, "\n")] = 0;
  name = string_from(buff, &error);
  if (error != ERROR_SUCCESS)
  {
    fputs(error_message(error), stderr);
    return;
  }

  memset(buff, 0, sizeof(buff));
  printf("\tEntre com a descrição do produto (opcional): ");
  if (fgets(buff, sizeof(buff), stdin) == NULL)
  {
    fputs(error_message(ERROR_INPUT), stderr);
    return;
  }
  buff[strcspn(buff, "\n")] = 0;
  description = string_from(buff, &error);
  if (error != ERROR_SUCCESS)
  {
    string_free(name);
    fputs(error_message(error), stderr);
    return;
  }

  product_init(&product, name, description);
  product_list_push(products, &product, &error);
  if (error != ERROR_SUCCESS)
  {
    string_free(name);
    string_free(description);
    product_clear(&product);
    fputs(error_message(error), stderr);
    return;
  }

  puts("Produto cadastrado com sucesso!");
}

// Remove um produto
void products_remove(ProductList *products)
{
  char name[BASE_STRING_SIZE] = {0};

  printf("\tEntre com o nome do produto: ");
  if (fgets(name, sizeof(name), stdin) == NULL)
  {
    fputs(error_message(ERROR_INPUT), stderr);
    return;
  }
  name[strcspn(name, "\n")] = 0;

  Product *product = product_list_find(products, name);
  if (product == NULL)
  {
    printf("Produto %s não encontrado!\n", name);
    return;
  }

  product_list_remove(products, product);
  puts("Produto removido com sucesso!");
}

// Dá um lance em um produto
void products_bid(ProductList *products, UserList *users)
{
  Error error;
  char user_name[BASE_STRING_SIZE] = {0};
  char product_name[BASE_STRING_SIZE] = {0};
  float value;

  printf("\tEntre com seu nome: ");
  if (fgets(user_name, sizeof(user_name), stdin) == NULL)
  {
    fputs(error_message(ERROR_INPUT), stderr);
    return;
  }
  user_name[strcspn(user_name, "\n")] = 0;

  printf("\tEntre com o valor do lance: R$ ");
  while (scanf(" %f%*c", &value) != 1)
  {
    fputs(error_message(ERROR_INPUT), stderr);
    if (scanf("%*[^\n]") == EOF)
    {
      fputs(error_message(ERROR_INPUT), stderr);
      break;
    }
    printf("\tEntre com o valor do lance: R$ ");
  }

  printf("\tEntre com o nome do produto: ");
  if (fgets(product_name, sizeof(product_name), stdin) == NULL)
  {
    fputs(error_message(ERROR_INPUT), stderr);
    return;
  }
  product_name[strcspn(product_name, "\n")] = 0;

  Product *product = product_list_find(products, product_name);
  if (product == NULL)
  {
    printf("Seu lance pelo(a) %s não foi aceito. Produto não encontrado\n", product_name);
    return;
  }

  User *user = user_list_find(users, user_name);
  if (user == NULL)
  {
    User new_user;
    String *new_user_name;

    new_user_name = string_from(user_name, &error);
    if (error != ERROR_SUCCESS)
    {
      fputs(error_message(error), stderr);
      return;
    }

    user_init(&new_user, new_user_name);
    user = user_list_push(users, &new_user, &error);
    if (error != ERROR_SUCCESS)
    {
      user_clear(&new_user);
      fputs(error_message(error), stderr);
      return;
    }
  }

  if (product_bid_add(product, user, value, &error) == true)
  {
    puts("Lance dado com sucesso!");
  }
  else
  {
    if (error != ERROR_SUCCESS)
    {
      fputs(error_message(error), stderr);
    }
    else
    {
      printf("Seu lance pelo(a) %s não foi aceito. Você precisa dar um lance maior!\n", string_cstr(product->name));
    }
  }
}

// Lista produtos e lances
void products_show(ProductList *products)
{
  if (products->len == 0)
  {
    puts("Nenhum produto cadastrado!");
    return;
  }

  for (ListBlock *list_block = product_list_first(products); list_block != NULL; list_block = product_list_next(list_block))
  {
    Product *product = product_list_get(list_block);
    printf("\t%s\n", string_cstr(product->name));

    if (product->description != NULL)
    {
      printf("\t\tDescrição: %s\n", string_cstr(product->description));
    }
    if (product->bids.len == 0)
    {
      puts("\t\tNenhum lance dado para o produto!");
      continue;
    }

    for (ListBlock *bid_block = product_bid_first(product); bid_block != NULL; bid_block = product_bid_next(bid_block))
    {
      bool first = true;
      Bid *bid = product_bid_get(bid_block);
      if (bid->users.len > 1)
      {
        printf("\t\t%lu", bid->users.len);
      }
      else
      {
        printf("\t\t%lu", bid->users.len);
      }
      printf(" lance de R$ %.2f: ", bid->value);

      for (ListBlock *user_block = bid_user_first(bid); user_block != NULL; user_block = bid_user_next(user_block))
      {
        User *user = bid_user_get(user_block);
        if (first)
        {
          first = true;
        }
        else
        {
          putchar(',');
        }
        printf("%s ", string_cstr(user->name));
      }
      putchar('\n');
    }
  }
  puts("Listagem completa!");
}

// Lista os produtos que cada usuário não deu lance
void users_missing_bids(UserList *users, ProductList *products)
{
  bool missing = false;
  for (ListBlock *list_block = user_list_first(users); list_block != NULL; list_block = user_list_next(list_block))
  {
    User *user = user_list_get(list_block);
    bool first = true;
    for (ListBlock *product_block = product_list_first(products); product_block != NULL; product_block = product_list_next(product_block))
    {
      bool found = false;
      Product *product = product_list_get(product_block);
      for (ListBlock *bid_block = user_bid_first(user); bid_block != NULL; bid_block = user_bid_next(bid_block))
      {
        Bid *bid = user_bid_get(bid_block);
        if (bid->product == product)
        {
          found = true;
          break;
        }
      }
      if (!found)
      {
        if (!missing)
        {
          missing = true;
        }
        if (first)
        {
          printf("\tpara %s: não gostaria de dar um lance pelo(a) %s?\n", string_cstr(user->name), string_cstr(product->name));
          first = false;
        }
        else
        {
          printf("\tnão gostaria de dar um lance pelo(a) %s?\n", string_cstr(product->name));
        }
      }
    }
  }
  if (missing)
  {
    puts("Listagem completa!");
  }
  else
  {
    puts("Todos os usuários deram lances para todos os produtos!");
  }
}

// Encerra o leilão, mostrando o lance vencedor de cada produto
void end_auction(ProductList *products, UserList *users)
{
  for (ListBlock *list_block = product_list_first(products); list_block != NULL; list_block = product_list_next(list_block))
  {
    Product *product = product_list_get(list_block);
    printf("\t%s: ", string_cstr(product->name));
    Bid *bid = product_end_auction(product);
    if (bid == NULL)
    {
      puts("nenhum lance foi dado para o produto!");
    }
    else
    {
      User *winner = bid_end(bid);
      printf("%s comprou por R$ %.2f\n", string_cstr(winner->name), bid->value);
    }
  }

  product_list_clear(products);
  user_list_clear(users);

  puts("Leilão encerrado!");
}

int main()
{
  ProductList products;
  product_list_init(&products);
  UserList users;
  user_list_init(&users);

  setlocale(LC_ALL, "");

  puts("Caro usuário, suas opções são:\n \
  \t1) cadastrar um produto\n \
  \t2) listar produtos e lances\n \
  \t3) dar um lance\n \
  \t4) listar outros produtos para lances\n \
  \t5) encerrar leilão\n \
  \t6) remover produto\n \
  \t7) sair do programa");

  while (true)
  {
    unsigned char opt;

    puts("\nO que deseja fazer?");

    printf("Resposta: ");
    while (scanf(" %hhu%*c", &opt) != 1)
    {
      fputs(error_message(ERROR_INPUT), stderr);
      if (scanf("%*[^\n]") == EOF)
      {
        fputs(error_message(ERROR_INPUT), stderr);
        break;
      }
      printf("\nResposta: ");
    }

    switch (opt)
    {
    case (1):
      products_add(&products);
      break;
    case (2):
      products_show(&products);
      break;
    case (3):
      products_bid(&products, &users);
      break;
    case (4):
      users_missing_bids(&users, &products);
      break;
    case (5):
      end_auction(&products, &users);
      break;
    case (6):
      products_remove(&products);
      break;
    case (7):
      product_list_clear(&products);
      user_list_clear(&users);
      puts("Programa encerrado!");
      return EXIT_SUCCESS;
    default:
      puts("Opção inválida!");
    }
  }

  return EXIT_SUCCESS;
}
