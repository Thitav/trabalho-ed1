#include "error.h"
#include <stdio.h>

char *error_message(Error error)
{
  switch (error)
  {
  case ERROR_SUCCESS:
    return "Nenhum erro identificado";
    break;
  case ERROR_MALLOC:
    return "Erro: não foi possível alocar memória";
    break;
  case ERROR_INPUT:
    return "Erro: entrada inválida";
    break;
  default:
    return "Erro: sem mensagem disponível";
  }
}
