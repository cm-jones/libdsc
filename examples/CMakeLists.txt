# Add example executables
add_executable(vector_example vector_example.c)
add_executable(unordered_map_example unordered_map_example.c)
add_executable(unordered_set_example unordered_set_example.c)
add_executable(queue_example queue_example.c)
add_executable(stack_example stack_example.c)
add_executable(forward_list_example forward_list_example.c)
add_executable(list_example list_example.c)

# Configure example targets
foreach(example_target
    vector_example
    unordered_map_example
    unordered_set_example
    queue_example
    stack_example
    forward_list_example
    list_example
)
    target_link_libraries(${example_target}
        PRIVATE
            dsc
    )
    target_include_directories(${example_target}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/include
    )
endforeach()
