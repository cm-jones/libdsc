# libdsc: Data Structures for C

[![build](https://github.com/cm-jones/dsc/actions/workflows/c.yml/badge.svg)](https://github.com/cm-jones/dsc/actions/workflows/c.yml) [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## Description

libdsc is an open-source C library featuring robust and efficient implementations of essential data
structures--including vectors, stacks, queues, lists, sets, and maps--with interfaces closely matching their
counterparts in the C++ standard library for familiarity and ease of use.

## Usage

To use libdsc in your C project, follow these steps:

1. Obtain the library files:
   - Either compile the library yourself (see "Building the Library" section below) or download the pre-compiled library files.

2. Include the header file in your C source file:
   ```c
   #include <libdsc.h>
   ```

3. Link against the library when compiling your program:
   - If using a static library (`libdsc.a`):
     ```
     gcc -o program program.c -L/path/to/library -ldsc
     ```
   - If using a shared library (`libdsc.so`):
     ```
     gcc -o program program.c -L/path/to/library -ldsc
     ```
     Make sure to add the library directory to your `LD_LIBRARY_PATH` environment variable.

4. Use the library functions in your code, for example:
   ```c
   struct dsc_list_t *list = dsc_list_create();

   dsc_list_append(list, 10); // [10]
   dsc_list_prepend(list, 5); // [5, 10]
   dsc_list_insert(list, 3, 1); // [5, 3, 10]
   dsc_list_get_length(list); // returns 3

   // Use other list functions as needed ...

   dsc_list_destroy(list);
   ```

## Building the Library

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
   This will generate the static library (`libdsc.a`) and the shared library (`libdsc.so`) in the project directory.

4. (Optional) Install the library and header files:
   ```
   sudo make install
   ```
   This will copy the library files to `/usr/local/lib` and the header file to `/usr/local/include`.

## API Documentation

Detailed API documentation for libdsc can be found in the `include` directory.

## Contributing

If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request on the [GitHub repository](https://github.com/cm-jones/libdsc).

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).
