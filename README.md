<p align="center" style="margin: 0; padding: 0;">
  <img src="assets/logo.png" alt="libdsc logo" width="200" height="200" style="vertical-align: middle;">
</p>

# libdsc

[![CI](https://github.com/cm-jones/libdsc/actions/workflows/ci.yaml/badge.svg)](https://github.com/cm-jones/libdsc/actions/workflows/ci.yaml)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cb3382e664b54cb7b1f023424fcc774c)](https://app.codacy.com/gh/cm-jones/libdsc/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
[![Codecov](https://codecov.io/gh/cm-jones/libdsc/branch/main/graph/badge.svg)](https://codecov.io/gh/cm-jones/libdsc)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

`libdsc` is an open-source C library featuring generic and memory-safe implementations of various containers provided by the C++ Standard Library.

## Features

`libdsc` implements the following containers:

- `vector`: dynamically-sized array
- `forward_list`: singly-linked list
- `list`: doubly-linked list
- `stack`: LIFO container
- `queue`: FIFO container
- `unordered_map`: hash table for key-value pairs
- `unordered_set`: hash table for unique elements

All containers are:

- Generic (can store any data type)
- Memory safe (with proper error handling)
- Thoroughly tested
- Benchmarked against C++ Standard Library counterparts

## Installing from source

First, build the project:

```bash
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_BENCHMARKS=OFF -DBUILD_EXAMPLES=OFF
make
```

Then, to install the library system-wide:

```bash
sudo make install
```

This will install:

- Library files to `/usr/local/lib`
- Header files to `/usr/local/include/libdsc`
- CMake configuration files to `/usr/local/lib/cmake/libdsc`

## Installing from package

On Debian-based Linux distributions:

```bash
sudo dpkg -i libdsc-<current_version>.deb
```

On RPM-based Linux distributions:

```bash

```

## Usage

```c
#include <libdsc/vector.h>
#include <libdsc/list.h>

// Include other containers as needed ...

#include <stdio.h>

int main(int argc, char *argv[]) {
    // Create a vector of integers
    dsc_vector *vec = vector_create(sizeof(int));

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
    dsc_list *list = list_create(sizeof(int));

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

    return EXIT_SUCCESS;
}
```

More examples can be found in the `examples` directory.

## Testing

Google Test is used for unit testing. To run the tests, after building the project:

```bash
cd build
ctest --output-on-failure
```

## Benchmarking

Google Benchmark is used to measure the performance of libdsc's containers against their equivalents in the C++ Standard Library. Benchmarks are run weekly automatically via GitHub Actions.  You can also run the benchmarks locally:

```bash
mkdir -p build
cd build
cmake .. -DBUILD_BENCHMARKS=ON
make
cd benchmarks
./benchmark_*
```

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) carefully before you attempt to make contributions to this project.

## License

`libdsc` is licensed under the GPLv3. See [LICENSE](LICENSE) for details.
