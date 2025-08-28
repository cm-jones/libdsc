cmake_minimum_required(VERSION 3.14)
project(libdsc VERSION 0.1.0 LANGUAGES C CXX)

# Project description
set(PROJECT_DESCRIPTION "Reimplementations of C++ Standard Library containers in C")
set(PROJECT_URL "https://github.com/cm-jones/libdsc")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set C++ standard for tests and benchmarks
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

# Compiler feature detection
set(COMPILER_SUPPORTS_GNU_CLANG FALSE)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    set(COMPILER_SUPPORTS_GNU_CLANG TRUE)
endif()

# Debug and Release build flags
if(COMPILER_SUPPORTS_GNU_CLANG)
    # Debug build flags
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -fno-omit-frame-pointer")

    # Release build flags
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# Coverage support
if(ENABLE_COVERAGE AND COMPILER_SUPPORTS_GNU_CLANG)
    message(STATUS "Enabling coverage reporting")
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

# Sanitizers for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND COMPILER_SUPPORTS_GNU_CLANG)
    message(STATUS "Enabling sanitizers for Debug build")
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

# Library target
add_library(dsc
    src/vector.c
    src/unordered_map.c
    src/unordered_set.c
    src/queue.c
    src/stack.c
    src/forward_list.c
    src/list.c
)

# Add alias for modern CMake usage
add_library(libdsc::dsc ALIAS dsc)

# Set library properties
set_target_properties(dsc PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME dsc
    C_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

# Add strict warning flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(dsc PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wformat=2
        -Wno-unused-parameter
        -Wshadow
        -Wwrite-strings
        -Wstrict-prototypes
        -Wold-style-definition
        -Wredundant-decls
        -Wnested-externs
        -Wmissing-include-dirs
    )
endif()

# Include directories
target_include_directories(dsc
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Install rules
include(GNUInstallDirs)

# Install library
install(TARGETS dsc
    EXPORT libdsc-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(DIRECTORY include/libdsc
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

# Install CMake config files
install(EXPORT libdsc-targets
    FILE libdsc-targets.cmake
    NAMESPACE libdsc::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libdsc
)

# Create CMake config file
include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/libdsc-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/libdsc-config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libdsc
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/libdsc-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/libdsc-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/libdsc-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libdsc
)

# Generate and install pkg-config file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/libdsc.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/libdsc.pc"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/libdsc.pc"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

# Add subdirectories based on options
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Print configuration summary
message(STATUS "")
message(STATUS "libdsc ${PROJECT_VERSION} configuration summary:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  Build tests: ${BUILD_TESTS}")
message(STATUS "  Build benchmarks: ${BUILD_BENCHMARKS}")
message(STATUS "  Build examples: ${BUILD_EXAMPLES}")
message(STATUS "  Enable coverage: ${ENABLE_COVERAGE}")
message(STATUS "")
