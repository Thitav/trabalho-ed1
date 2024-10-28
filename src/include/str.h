#ifndef STRING_H
#define STRING_H

#include "block.h"

typedef Block String;

// Inicializa a string a partir de uma string C
String *string_from(char *src, Error *error);
// Retorna a string em formato de string C
char *string_cstr(String *string);
// Comapara duas strings
int string_cmp(String *string1, String *string2);
// Compara uma string com uma string C
int string_cmp_cstr(String *string, char *cstr);
// Libera a memória alocada para a string
void string_free(String *string);

#endif
