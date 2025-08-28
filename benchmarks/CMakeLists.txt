# Configure Google Benchmark
include(FetchContent)

# Set FetchContent options for better reliability
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# Configure benchmark options before fetching
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.8.3
    GIT_SHALLOW TRUE
    FIND_PACKAGE_ARGS NAMES benchmark
)

# Add relaxed warning flags for benchmark
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-Wno-format-nonliteral)
endif()

FetchContent_MakeAvailable(benchmark)

# Add benchmark executables
add_executable(benchmark_vector benchmark_vector.cpp)
add_executable(benchmark_unordered_map benchmark_unordered_map.cpp)
add_executable(benchmark_unordered_set benchmark_unordered_set.cpp)
add_executable(benchmark_queue benchmark_queue.cpp)
add_executable(benchmark_stack benchmark_stack.cpp)
add_executable(benchmark_forward_list benchmark_forward_list.cpp)
add_executable(benchmark_list benchmark_list.cpp)

# Configure benchmark targets
foreach(benchmark_target
    benchmark_vector
    benchmark_unordered_map
    benchmark_unordered_set
    benchmark_queue
    benchmark_stack
    benchmark_forward_list
    benchmark_list
)
    target_link_libraries(${benchmark_target}
        PRIVATE
            dsc
            benchmark::benchmark
            benchmark::benchmark_main
    )
    target_include_directories(${benchmark_target}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/include
    )
endforeach()
