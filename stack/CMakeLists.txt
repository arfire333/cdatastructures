add_executable(stack stack.c)

add_executable( test_stack 
    test_stack.cpp
)

target_link_libraries( test_stack 
    GTest::gtest_main
)

gtest_discover_tests(test_stack)