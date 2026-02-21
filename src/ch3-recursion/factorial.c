#include <stdio.h>
int factorial(int n) {
  if (n < 0) {
    return 0;
  } else if (n == 0) {
    printf("Returning 1\n");
    return 1;
  } else {
    printf("%d x factorial(%d)\n", n, n - 1);
    const int f = factorial(n - 1);
    const int result = n * f;
    printf("%d x factorial(%d) = %d\n", n, n - 1, result);
    return result;
  }
}

int main(void) {
  int n = 7;
  printf("Factorial of %d is %d", n, factorial(n));
}
