#include "h2.h"

unsigned long h2(const char *data) {
  unsigned long h = 0;
  int c = 0;
  while ((c = *data++))
    h = (h << 5) - h + c;
  return h;
}
