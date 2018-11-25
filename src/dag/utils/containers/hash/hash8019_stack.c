/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdlib.h>

#include "utils/containers/hash/hash8019_stack.h"

bool hash8019_stack_empty(hash8019_stack_t const stack) { return (stack == NULL); }

retcode_t hash8019_stack_push(hash8019_stack_t *const stack,
                          flex_trit_t const *const hash) {
  hash8019_stack_entry_t *entry = NULL;

  if ((entry = malloc(sizeof(hash8019_stack_entry_t))) == NULL) {
    return RC_UTILS_OOM;
  }
  memcpy(entry->hash, hash, FLEX_TRIT_SIZE_8019);
  LL_PREPEND(*stack, entry);
  return RC_OK;
}

void hash8019_stack_pop(hash8019_stack_t *const stack) {
  hash8019_stack_entry_t *tmp = NULL;

  tmp = *stack;
  LL_DELETE(*stack, *stack);
  free(tmp);
}

flex_trit_t *hash8019_stack_peek(hash8019_stack_t const stack) {
  return (flex_trit_t *)(stack->hash);
}

void hash8019_stack_free(hash8019_stack_t *const stack) {
  hash8019_stack_entry_t *iter = NULL, *tmp = NULL;

  LL_FOREACH_SAFE(*stack, iter, tmp) {
    LL_DELETE(*stack, iter);
    free(iter);
  }
}

size_t hash8019_stack_count(hash8019_stack_t const stack) {
  hash8019_stack_t curr = stack;
  size_t count = 0;
  while (curr != NULL) {
    ++count;
    curr = curr->next;
  }
  return count;
}
