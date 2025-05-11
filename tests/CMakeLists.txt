# Configure Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Add test executables
add_executable(test_vector test_vector.cpp)
add_executable(test_unordered_map test_unordered_map.cpp)
add_executable(test_unordered_set test_unordered_set.cpp)
add_executable(test_queue test_queue.cpp)
add_executable(test_stack test_stack.cpp)
add_executable(test_forward_list test_forward_list.cpp)
add_executable(test_list test_list.cpp)

# Configure test targets
foreach(test_target
    test_vector
    test_unordered_map
    test_unordered_set
    test_queue
    test_stack
    test_forward_list
    test_list
)
    target_link_libraries(${test_target}
        PRIVATE
            dsc
            gtest
            gtest_main
    )
    target_include_directories(${test_target}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/include
    )
    add_test(NAME ${test_target} COMMAND ${test_target})
endforeach()
