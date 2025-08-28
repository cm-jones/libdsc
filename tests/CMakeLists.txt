# Configure Google Test
include(FetchContent)

# Set FetchContent options for better reliability
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
    GIT_SHALLOW TRUE
    FIND_PACKAGE_ARGS NAMES GTest
)

# Make googletest available
FetchContent_MakeAvailable(googletest)

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

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
