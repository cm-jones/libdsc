<p align="center">
  <img src="assets/logo.png" alt="logo" width="200" height="200" style="vertical-align: middle;">
</p>

# libdsc

[![CI](https://github.com/cm-jones/libdsc/actions/workflows/ci.yaml/badge.svg)](https://github.com/cm-jones/libdsc/actions/workflows/ci.yaml)
[![Benchmarks](https://github.com/cm-jones/libdsc/actions/workflows/benchmark.yaml/badge.svg)](https://github.com/cm-jones/libdsc/actions/workflows/benchmark.yaml)
[![Codecov](https://codecov.io/gh/cm-jones/libdsc/branch/main/graph/badge.svg)](https://codecov.io/gh/cm-jones/libdsc)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

libdsc is an open-source C library that features generic implementations of several C++ Standard Library containers.

## Features

- **Vector**: Dynamically-sized array
- **Forward List**: Singly-linked list
- **List**: Doubly-linked list
- **Stack**: LIFO container
- **Queue**: FIFO container
- **Unordered Map**: Hash table for key-value pairs
- **Unordered Set**: Hash table for unique elements

All of these implementations are:

- Generic (can store any data type)
- Memory safe (with proper error handling)
- Thoroughly tested
- Performance benchmarked against C++ counterparts

## Installing from source

First, build the project:

```bash
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_BENCHMARKS=OFF -DBUILD_EXAMPLES=OFF
make
```

Then, install the library system-wide:

```bash
cd build
sudo make install
```

This will install:

- Library files to `/usr/local/lib`
- Header files to `/usr/local/include/libdsc`
- CMake configuration files to `/usr/local/lib/cmake/libdsc`

## Usage

```c
#include <libdsc/vector.h>
#include <libdsc/list.h>

#include <stdio.h>

int main() {
    // Create a vector of integers
    dsc_vector_t *vec = vector_create(sizeof(int));

    // Push some values
    for (size_t i = 0; i < 5; ++i) {
        vector_push_back(vec, &i);
    }

    // Access elements
    for (size_t i = 0; i < vector_size(vec); ++i) {
        int *value = (int *) vector_get(vec, i);
        printf("%d ", *value);
    }

    // Clean up
    vector_destroy(vec);

    // Create a list of integers
    dsc_list_t *list = list_create(sizeof(int));

    // Push some values
    for (size_t i = 0; i < 5; ++i) {
        list_push_back(list, &i);
    }

    // Iterate through elements
    list_node_t *current = list_begin(list);
    while (current) {
        int *value = (int *) current->data;
        printf("%d ", *value);
        current = current->next;
    }

    // Clean up
    list_destroy(list);

    return 0;
}
```

More examples can be found in the `examples` directory.

## Testing

libdsc uses Google Test for unit testing. To run the tests:

```bash
cd build
ctest --output-on-failure
```

## Benchmarking

Google Benchmark is used for benchmarking libdsc containers against the equivalent containers in the C++ Standard Library. Benchmarks are run weekly and can be found in the [Actions tab](https://github.com/cm-jones/libdsc/actions/workflows/benchmark.yaml) under the Benchmarks workflow. You can also run benchmarks locally:

```bash
mkdir -p build
cd build
cmake .. -DBUILD_BENCHMARKS=ON
make
cd benchmarks
./benchmark_*
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md).

## License

This project is licensed under the GPLv3. See [LICENSE](LICENSE) for details.
