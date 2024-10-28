#ifndef ERRORS_H
#define ERRORS_H

typedef enum
{
  ERROR_SUCCESS, // Sem erro
  ERROR_MALLOC,  // Erro ao alocar memória
  ERROR_INPUT,   // Erro ao ler entrada do usuário
} Error;

// Retorna a mensagem de erro correspondente ao erro passado
char *error_message(Error error);

#endif
