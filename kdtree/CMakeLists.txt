add_executable(kdtree kdtree.c)

add_executable( test_kdtree 
    test_kdtree.cpp
)

target_link_libraries( test_kdtree 
    GTest::gtest_main
)

gtest_discover_tests(test_kdtree)