# DSC Type System

The DSC library provides a type system to support generic containers that can store elements of different data types. The type system is defined in the `dsc_type.h` header file and includes an enumeration `DSCType` representing various data types.

## DSCType Enumeration

The `DSCType` enumeration defines a set of constants representing different data types that can be used with the containers in the DSC library. The available constants are:

- `DSC_TYPE_UNKNOWN`: Unknown or unrecognized type.
- `DSC_TYPE_BOOL`: Boolean type.
- `DSC_TYPE_CHAR`: Character type.
- `DSC_TYPE_INT`: Integer type.
- `DSC_TYPE_FLOAT`: Single-precision floating-point type.
- `DSC_TYPE_DOUBLE`: Double-precision floating-point type.
- `DSC_TYPE_STRING`: String type (character pointer).
- `DSC_TYPE_COUNT`: Solely used to check for invalid types.


These constants can be used to specify the type of elements stored in the containers provided by the DSC library.

## Conclusion

The DSC type system provides a way to handle different data types in generic containers. By using the `DSCType` enum, you can specify the types of elements stored in the containers.
