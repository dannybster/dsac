add_executable(chhash_table_test ../ch5-linked-lists/list.c chhash_table_test.c chhash_table.c djb2.c)
add_test(NAME chhash_table_test COMMAND chhash_table_test)
set_tests_properties(chhash_table_test PROPERTIES LABELS "asan")
add_test(NAME chhash_table_test_leaks COMMAND leaks --atExit -- $<TARGET_FILE:chhash_table_test>)
set_tests_properties(chhash_table_test_leaks PROPERTIES LABELS "leaks")

add_executable(oahash_table_test ../ch5-linked-lists/list.c oahash_table_test.c oahash_table.c djb2.c h2.c)
add_test(NAME oahash_table_test COMMAND oahash_table_test)
set_tests_properties(oahash_table_test PROPERTIES LABELS "asan")
add_test(NAME oahash_table_test_leaks COMMAND leaks --atExit -- $<TARGET_FILE:oahash_table_test>)
set_tests_properties(oahash_table_test_leaks PROPERTIES LABELS "leaks")

