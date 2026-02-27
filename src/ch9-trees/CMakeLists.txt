add_executable(bi_tree_test  bi_tree_test.c bi_tree.c)
add_test(NAME bi_tree_test COMMAND bi_tree_test)
set_tests_properties(bi_tree_test PROPERTIES LABELS "asan")
add_test(NAME bi_tree_test_leaks COMMAND leaks --atExit -- $<TARGET_FILE:bi_tree_test>)
set_tests_properties(bi_tree_test_leaks PROPERTIES LABELS "leaks")

