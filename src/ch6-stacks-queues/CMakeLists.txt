add_executable(stack_test stack_test.c stack.c)
add_test(NAME stack_test COMMAND stack_test)
set_tests_properties(stack_test PROPERTIES LABELS "asan")
add_test(NAME stack_test_leaks COMMAND leaks --atExit -- $<TARGET_FILE:stack_test>)
set_tests_properties(stack_test_leaks PROPERTIES LABELS "leaks")

add_executable(queue_test queue_test.c queue.c ../ch5-linked-lists/list.c)
add_test(NAME queue_test COMMAND queue_test)
set_tests_properties(queue_test PROPERTIES LABELS "asan")
add_test(NAME queue_test_leaks COMMAND leaks --atExit -- $<TARGET_FILE:queue_test>)
set_tests_properties(queue_test_leaks PROPERTIES LABELS "leaks")

