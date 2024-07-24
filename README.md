<p align="center">
  <img src="assets/logo.png" alt="logo" width="300" height="300" style="vertical-align: middle;">
</p>

# libdsc: Data Structures for C

[![build](https://github.com/cm-jones/dsc/actions/workflows/c.yml/badge.svg)](https://github.com/cm-jones/dsc/actions/workflows/c.yml) [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## Description

libdsc is an open-source C library featuring robust, efficient, and generic implementations of the following containers:

- Vectors: similar to `std::vector`
- Lists:   similar to `std::list`
- Stacks:  similar to `std::stack`
- Queues:  similar to `std::queue`
- Sets:    similar to `std::unordered_set`
- Maps:    similar to `std::unordered_map`

The APIs closely resemble those found for the corresponding containers in the C++ Standard Library, which provides familiarity and ease of use to C++ developers.

## Version

The current version of libdsc is [0.1.0-alpha](https://github.com/cm-jones/libdsc/releases/tag/v0.1.0-alpha).

## Usage

To use libdsc in your C project, follow these steps:

1. Obtain the library files:
   - Either compile the library yourself (see [Build](#Build) section below) or download the pre-compiled library files.

2. Include the header file in your C source file:
   ```c
   #include <libdsc.h>
   ```

3. Link against the library when compiling your program:
   - If using a static (`libdsc.a`) or shared (`libdsc.so`) library:
     ```
     gcc -o program program.c -L/path/to/library -ldsc
     ```
     Make sure to add the library directory to your `LD_LIBRARY_PATH` environment variable.

4. Use the library functions in your code, for example:
   ```c
   DSCSet set = dsc_set_init(DSC_TYPE_INT);
   if (!set) {
      // Handle memory allocation error ...
   }

   for (size_t i = 0; i < 100; ++i) {
      if (!dsc_set_insert(set, i)) {
         DSCError errno = dsc_error_get(set);
         // Handle error code ...
      }
   }
   
   dsc_set_insert(set, 0);    // Returns false
   dsc_set_contains(set, 99); // Returns true
   dsc_set_erase(set, 53);    // Returns true
   int size = dsc_set_size(set); // Returns 99

   // Use other set functions as needed ...

   dsc_set_deinit(set);
   ```

## Build

To build libdsc yourself, follow these steps:

1. Clone the repository:
   ```
   git clone https://github.com/cm-jones/libdsc.git
   ```

2. Change into the project directory:
   ```
   cd libdsc
   ```

3. Compile the library using the provided Makefile:
   ```
   make
   ```
   This will generate the static library (`libdsc.a`) and the shared library (`libdsc.so`) in the project's root directory.

4. (Optional) Install the library and header files:
   ```
   sudo make install
   ```
   This will copy the library files to `/usr/local/lib` and the header file to `/usr/local/include`.

## Documentation

Detailed documentation for libdsc can be found under [docs/](docs/).

## Contributing

If you find any issues or have suggestions for improvements, feel free to [open an issue](https://github.com/cm-jones/libdsc/issues/new) or submit a [pull request](https://github.com/cm-jones/libdsc/compare).

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).
