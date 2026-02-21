#include "stack.h"
#include <stdlib.h>
#include <string.h>

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
  if (stack->size == stack->buffer_size) {
    int new_size = stack->buffer_size * 2;
    void *new_buffer;
    if ((new_buffer = realloc(stack->elements, new_size * sizeof(void *))) ==
        NULL) {
      return -1;
    }

    stack->buffer_size = new_size;
    stack->elements = new_buffer;
  }

  stack->elements[stack->size] = data;
  stack->size += 1;

  return 0;
}

int stack_pop(Stack *stack, void **data) {
  if (stack->size == 0) {
    return -1;
  }

  stack->size -= 1;
  *data = stack->elements[stack->size];
  stack->elements[stack->size] = NULL;
  return 0;
}

int stack_peek(const Stack *stack, void **data) {
  if (stack->size == 0) {
    return -1;
  }

  *data = stack->elements[stack->size - 1];
  return 0;
}

void stack_destroy(Stack *stack) {
  void *data;
  while (stack_pop(stack, &data) == 0) {
    if (stack->destroy) {
      stack->destroy(data);
    }
  }
  free(stack->elements);

  memset(stack, 0, sizeof(Stack));
}
