# Data Structures & Algorithms in C

Working through *Mastering Algorithms with C* by Kyle Loudon.

## Build

```bash
# Configure and build (ASan enabled by default)
cmake -S . -B build
cmake --build build

# Configure without ASan (for leak testing)
cmake -S . -B build -DENABLE_ASAN=OFF
cmake --build build
```

## Tests

```bash
# Run all tests (exclude leak tests when using ASan build)
ctest --test-dir build -LE leaks

# Run only leak tests (reconfigure with ASan off first)
ctest --test-dir build -L leaks

# Run with failure output
ctest --test-dir build -LE leaks --output-on-failure

# Run a specific test by name
ctest --test-dir build -R dlist_test
```

## Debugging

Debug with `lldb` or Neovim DAP (F5 continue, F9 breakpoint, F10 step over, F11 step into, F12 step out). Launch configs are in `.vscode/launch.json`.
