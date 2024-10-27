#include "str.h"
#include "block.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

String *string_from(char *src, Error *error)
{
  *error = ERROR_SUCCESS;
  size_t len = strlen(src);
  if (len == 0)
  {
    return NULL;
  }

  String *string = block_alloc(len + 1, error);
  if (*error != ERROR_SUCCESS || string == NULL)
  {
    return NULL;
  }

  strcpy(string->data, src);
  return string;
}

char *string_cstr(String *string)
{
  return string->data;
}

int string_cmp(String *string1, String *string2)
{
  return strcmp(string_cstr(string1), string_cstr(string2));
}

int string_cmp_cstr(String *string, char *cstr)
{
  return strcmp(string_cstr(string), cstr);
}

void string_free(String *string)
{
  block_free(string);
}
