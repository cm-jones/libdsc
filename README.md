<p align="center" style="margin: 0; padding: 0;">
  <img src="assets/logo.png" alt="libdsc logo" width="200" height="200" style="vertical-align: middle;">
</p>

# libdsc

[![CI](https://github.com/cm-jones/libdsc/actions/workflows/ci.yaml/badge.svg)](https://github.com/cm-jones/libdsc/actions/workflows/ci.yaml)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cb3382e664b54cb7b1f023424fcc774c)](https://app.codacy.com/gh/cm-jones/libdsc/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
[![Codecov](https://codecov.io/gh/cm-jones/libdsc/branch/main/graph/badge.svg)](https://codecov.io/gh/cm-jones/libdsc)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

libdsc is a free and open-source C library that provides generic implementations of various containers from the C++ Standard Library. It brings modern container functionality to the C programming language with well-tested, memory-safe, and high-performance implementations.

## Features

libdsc currently implements the following containers:

### Sequence Containers

- `dsc_vector`: dynamic array equivalent to `std::vector`

- `dsc_forward_list`: singly-linked list equivalent to `std::forward_list`

- `dsc_list`: doubly-linked list equivalent to `std::list`

### Unordered Associative Containers

- `dsc_unordered_map`: hash table with key-value pairs equivalent to `std::unordered_map`

- `dsc_unordered_set`: hash table for unique elements equivalent to `std::unordered_set`

### Container Adaptors

- `stack`: LIFO container adapter equivalent to `std::stack`

- `queue`: FIFO container adapter equivalent to `std::queue`

### Key Benefits
- **Generic**: Can store any data type using `void*` and element size
- **Memory-safe**: Comprehensive error handling and bounds checking
- **High-performance**: Benchmarked against C++ STL equivalents
- **Well-tested**: Extensive unit tests with Google Test
- **Professional**: Follows industry best practices for C libraries

See [ROADMAP.md](ROADMAP.md) for containers planned for future releases.

## Quick Start

### Basic Example

```c
#include <libdsc/vector.h>
#include <stdio.h>

int main() {
    // Create a vector of integers
    dsc_vector *vec = vector_create(sizeof(int));
    if (!vec) return 1;
    
    // Add some elements
    int values[] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < 5; i++) {
        vector_push_back(vec, &values[i]);
    }
    
    // Access elements
    printf("Vector size: %zu\n", vector_size(vec));
    int *first = (int*)vector_at(vec, 0);
    printf("First element: %d\n", *first);
    
    // Clean up
    vector_destroy(vec);
    return 0;
}
```

More complete examples can be found in the [`examples/`](examples/) directory.

## Installation

### From Source

#### Prerequisites

- CMake 3.14 or higher

- C11-compatible compiler (GCC, Clang, MSVC)

- Git

#### Build and Install

```bash
# Clone the repository
git clone https://github.com/cm-jones/libdsc.git
cd libdsc

# Create build directory
mkdir -p build && cd build

# Configure and build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_BENCHMARKS=OFF -DBUILD_EXAMPLES=OFF
make -j$(nproc)

# Install system-wide (optional)
sudo make install
```

This installs:
- Library files to `/usr/local/lib`
- Header files to `/usr/local/include/libdsc`
- CMake configuration files to `/usr/local/lib/cmake/libdsc`

### From Packages

#### Debian/Ubuntu
```bash
sudo dpkg -i libdsc-*.deb
```

#### Fedora/RHEL/CentOS
```bash
sudo rpm -i libdsc-*.rpm
```

#### Arch Linux
```bash
sudo pacman -U libdsc-*.pkg.tar.zst
```

### Using CMake

Add to your `CMakeLists.txt`:

```cmake
find_package(libdsc REQUIRED)
target_link_libraries(your_target libdsc::dsc)
```

## Documentation

- **API Reference**: Generated with Doxygen in [`docs/`](docs/)

- **Examples**: Complete usage examples in [`examples/`](examples/)

- **Contributing**: See [CONTRIBUTING.md](CONTRIBUTING.md)

- **Security**: See [SECURITY.md](SECURITY.md)

- **Code of Conduct**: See [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)

## Development

### Building with Tests

```bash
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
make -j$(nproc)
ctest --output-on-failure
```

### Running Benchmarks

```bash
mkdir build && cd build
cmake .. -DBUILD_BENCHMARKS=ON
make -j$(nproc)
cd benchmarks
./benchmark_vector
./benchmark_list
# ... other benchmarks
```

### Code Quality

```bash
# Format code
./scripts/format.sh

# Run linter
./scripts/lint.sh

# Generate documentation
./scripts/docs.sh
```

## Performance

libdsc containers are regularly benchmarked against their C++ STL equivalents. Performance results are available in our [CI benchmarks](https://github.com/cm-jones/libdsc/actions).

Key performance characteristics:
- **Vector**: Amortized O(1) push_back, O(1) random access
- **List**: O(1) insertion/deletion, O(n) search
- **Hash containers**: Average O(1) insertion/lookup, O(n) worst case

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) carefully before attempting to make any contributions.

## License

This project is licensed under the GNU General Public License v3.0. See [LICENSE](LICENSE) for details.
