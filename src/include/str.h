#ifndef STRING_H
#define STRING_H

#include "block.h"

typedef Block String;

String *string_from(char *src, Error *error);
char *string_cstr(String *string);
int string_cmp(String *string1, String *string2);
int string_cmp_cstr(String *string, char *cstr);
void string_free(String *string);

#endif
