<p align="center" style="margin: 0; padding: 0;">
  <img src="assets/logo.png" alt="libdsc logo" width="200" height="200" style="vertical-align: middle;">
</p>

# libdsc

<div align="center">

| Category | Status |
|:--------:|:------:|
| **Build** | [![CI](https://github.com/cm-jones/libdsc/actions/workflows/ci.yaml/badge.svg)](https://github.com/cm-jones/libdsc/actions/workflows/ci.yaml) |
| **Quality** | [![Codacy Badge](https://app.codacy.com/project/badge/Grade/cb3382e664b54cb7b1f023424fcc774c)](https://app.codacy.com/gh/cm-jones/libdsc/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade) |
| **Coverage** | [![Codecov](https://codecov.io/gh/cm-jones/libdsc/branch/main/graph/badge.svg)](https://codecov.io/gh/cm-jones/libdsc) |
| **License** | [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) |

</div>

libdsc is a free and open-source C library featuring generic reimplementations of containers provided by the C++ Standard Library.

## Features

libdsc currently reimplements the following containers:

### Sequence containers

- `std::vector`

- `std::forward_list`

- `std::list`

### Unordered associative containers

- `std::unordered_map`

- `std::unordered_set`

### Container adaptors

- `std::stack`

- `std::queue`

All of these (re)implementations are generic (can store any data type), memory-safe, and benchmarked against their counterparts in the C++ Standard Library.

See [ROADMAP.md](ROADMAP.md) for a list of containers we plan to (re)implement in the future.

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

On Debian-based Linux distributions (e.g., Debian, Ubuntu, Linux Mint):

```bash
sudo dpkg -i libdsc-*.deb
```

On RPM-based Linux distributions (e.g., Fedora, Red Hat):

```bash

```

## Usage

Simply include the relevant headers in your project, like so:

```c
#include <libdsc/vector.h>
#include <libdsc/list.h>
```

Complete examples can be found in the `examples/` directory.

## Testing

Google Test is used for unit testing. To run the tests, after building the project:

```bash
cd build
ctest --output-on-failure
```

## Benchmarking

Google Benchmark is used to measure the performance of libdsc's containers against their equivalents in the C++ Standard Library. Benchmarks are run weekly automatically via GitHub Actions.  You can also run the benchmarks locally:

Benchmarks are automatica

```bash
mkdir -p build
cd build
cmake .. -DBUILD_BENCHMARKS=ON
make
cd benchmarks
./benchmark_*
```

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) carefully before you attempt to make any contributions to this project.

## License

This project is licensed under the GPLv3. See [LICENSE](LICENSE) for details.
