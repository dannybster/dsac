#include "stack.h"
#include <stdlib.h>

int stack_init(Stack *stack, void (*destroy)(void *data),
               int initial_buffer_size) {
  if ((stack->elements = malloc(initial_buffer_size * sizeof(void *))) ==
      NULL) {
    return -1;
  }

  stack->buffer_size = initial_buffer_size;
  stack->size = 0;
  stack->destroy = destroy;

  return 0;
}

int stack_push(Stack *stack, void *data) {
  if (stack->size + 1 == stack->buffer_size) {
    int new_size = stack->buffer_size *= 2;
    void *new_buffer;
    if ((new_buffer = realloc(stack->elements,
                              stack->buffer_size * sizeof(void *))) == NULL) {
      return -1;
    }

    stack->buffer_size = new_size;
    stack->elements = new_buffer;
  }

  stack->elements[stack->size] = data;
  stack->size += 1;

  return 0;
}

int stack_pop(Stack *stack, void **data) { return -1; }
