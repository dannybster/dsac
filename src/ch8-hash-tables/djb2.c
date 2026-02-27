unsigned long djb2(const char *data) {
  unsigned long h = 5381;
  int c;
  while ((c = *data++))
    h = (h << 5) + h + c;
  return h;
}
