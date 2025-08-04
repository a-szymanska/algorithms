set(TEST_SOURCES
        algebra.cpp
        dynamic.cpp
        geometry.cpp
        graph.cpp
        matrix.cpp
        number.cpp
        sorting.cpp
        texts.cpp
        )

add_executable(test_suite ${TEST_SOURCES})

add_test(NAME AllTests COMMAND test_suite)
