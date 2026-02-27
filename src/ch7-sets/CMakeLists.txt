add_executable(set_test ../ch5-linked-lists/list.c set_test.c set.c)
add_test(NAME set_test COMMAND set_test)
set_tests_properties(set_test PROPERTIES LABELS "asan")
add_test(NAME set_test_leaks COMMAND leaks --atExit -- $<TARGET_FILE:set_test>)
set_tests_properties(set_test_leaks PROPERTIES LABELS "leaks")

