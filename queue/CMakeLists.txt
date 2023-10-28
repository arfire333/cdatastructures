add_executable(queue queue.c)

add_executable( test_queue 
    test_queue.cpp
)

target_link_libraries( test_queue 
    GTest::gtest_main
)

gtest_discover_tests(test_queue)