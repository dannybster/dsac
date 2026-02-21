typedef struct Stack_ {
  int buffer_size;
  int size;
  void **elements;
  void (*destroy)(void *data);
} Stack;

int stack_init(Stack *stack, void (*destroy)(void *data),
               int initial_buffer_size);
int stack_pop(Stack *stack, void **data);
int stack_push(Stack *stack, void *data);
