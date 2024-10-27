#ifndef ERRORS_H
#define ERRORS_H

typedef enum
{
  ERROR_SUCCESS,
  ERROR_MALLOC,
  ERROR_INPUT,
} Error;

char *error_message(Error error);

#endif
