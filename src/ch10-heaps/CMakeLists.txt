add_executable(heap_test heap_test.c heap.c)
add_test(NAME heap_test COMMAND heap_test)
set_tests_properties(heap_test PROPERTIES LABELS "asan")
add_test(NAME heap_test_leaks COMMAND leaks --atExit -- $<TARGET_FILE:heap_test>)
set_tests_properties(heap_test_leaks PROPERTIES LABELS "leaks")

