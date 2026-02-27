cmake_minimum_required(VERSION 3.20)
project(dsa C)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 17)
set(CMAKE_STANDARD_REQUIRED ON)

# Turn on all warnings for supported compilers
if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

option(ENABLE_ASAN "Enable AddressSanitizer" ON)

if(ENABLE_ASAN)
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

enable_testing()

add_executable(hello src/hello.c)
add_subdirectory(src/ch3-recursion)
add_subdirectory(src/ch5-linked-lists)
add_subdirectory(src/ch6-stacks-queues)
add_subdirectory(src/ch7-sets)
add_subdirectory(src/ch8-hash-tables)
add_subdirectory(src/ch9-trees)
