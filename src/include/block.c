#include "block.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>

Block *block_alloc(size_t size, Error *error)
{
  *error = ERROR_SUCCESS;
  if (size == 0)
  {
    return NULL;
  }

  Block *block = malloc(sizeof(Block) + size);
  if (block == NULL)
  {
    *error = ERROR_MALLOC;
  }

  block->size = size;
  return block;
}

void block_copy_from(Block *block, void *src)
{
  memcpy(block->data, src, block->size);
}

void block_free(Block *block)
{
  free(block);
}
