<p align="center">
  <img src="assets/logo.png" alt="logo" width="200" height="200" style="vertical-align: middle;">
</p>

# libdsc

[![CI](https://github.com/cm-jones/libdsc/actions/workflows/ci.yaml/badge.svg)](https://github.com/cm-jones/libdsc/actions/workflows/ci.yml)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Generic implementations of some C++ STL containers in C. This library provides efficient, type-safe, and easy-to-use container implementations that mirror the functionality of their C++ counterparts.

## Features

- **Vector**: Dynamic array implementation with automatic resizing
- **Unordered Map**: Hash table implementation for key-value pairs
- **Unordered Set**: Hash table implementation for unique elements
- **Queue**: FIFO container implementation
- **Stack**: LIFO container implementation
- **Forward List**: Singly linked list implementation
- **List**: Doubly linked list implementation

All containers are:

- Generic (can store any data type)
- Memory safe (with proper error handling)
- Thoroughly tested
- Performance benchmarked against C++ counterparts

## Building

This project uses CMake as its build system. To build the library, tests, benchmarks, and examples:

```bash
mkdir build
cd build
cmake ..
make
```

### Build Options

- `BUILD_TESTS`: Build unit tests (ON by default)
- `BUILD_BENCHMARKS`: Build performance benchmarks (ON by default)
- `BUILD_EXAMPLES`: Build example programs (ON by default)

To disable any of these, set the option to OFF when running CMake:

```bash
cmake .. -DBUILD_TESTS=OFF -DBUILD_BENCHMARKS=OFF
```

## Testing

The project uses Google Test for unit testing. To run the tests:

```bash
cd build
ctest
```

Or run individual test executables:

```bash
./test_vector
./test_unordered_map
./test_unordered_set
./test_queue
./test_stack
./test_forward_list
./test_list
```

## Benchmarking

Performance benchmarks are implemented using Google Benchmark, comparing each container against its C++ standard library counterpart. To run the benchmarks:

```bash
./benchmark_vector
./benchmark_unordered_map
./benchmark_unordered_set
./benchmark_queue
./benchmark_stack
./benchmark_forward_list
./benchmark_list
```

## Usage Examples

### Vector

```c
#include <libdsc/vector.h>
#include <stdio.h>

int main() {
    // Create a vector of integers
    dsc_vector_t* vec = vector_create(sizeof(int));

    // Push some values
    for (size_t i = 0; i < 5; ++i) {
        vector_push_back(vec, &i);
    }

    // Access elements
    for (size_t i = 0; i < vector_size(vec); ++i) {
        int* value = (int*)vector_get(vec, i);
        printf("%d ", *value);
    }

    // Clean up
    vector_destroy(vec);
    return 0;
}
```

### List

```c
#include <libdsc/list.h>
#include <stdio.h>

int main() {
    // Create a list of integers
    dsc_list_t* list = list_create(sizeof(int));

    // Push some values
    for (size_t i = 0; i < 5; ++i) {
        list_push_back(list, &i);
    }

    // Iterate through elements
    list_node_t* current = list_begin(list);
    while (current) {
        int* value = (int*)current->data;
        printf("%d ", *value);
        current = current->next;
    }

    // Clean up
    list_destroy(list);
    return 0;
}
```

More examples can be found in the `examples` directory.

## Installation

To install the library system-wide:

```bash
cd build
sudo make install
```

This will install:

- Library files to `/usr/local/lib`
- Header files to `/usr/local/include/libdsc`
- CMake configuration files to `/usr/local/lib/cmake/libdsc`

## License

This project is licensed under the GNU GPLv3 - see the LICENSE file for details.
