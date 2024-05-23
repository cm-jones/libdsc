# DSC Type System

The DSC library provides a type system to support generic containers that can store elements of different data types. The type system is defined in the `dsc_type.h` header file and includes an enumeration `DSCType` representing various data types, as well as a function `dsc_type_of` for determining the type of a given data pointer.

## DSCType Enumeration

The `DSCType` enumeration defines a set of constants representing different data types that can be used with the containers in the DSC library. The available constants are:

- `DSC_TYPE_UNKNOWN`: Unknown or unrecognized type.
- `DSC_TYPE_CHAR`: Character type.
- `DSC_TYPE_UCHAR`: Unsigned character type.
- `DSC_TYPE_SHORT`: Short integer type.
- `DSC_TYPE_USHORT`: Unsigned short integer type.
- `DSC_TYPE_INT`: Integer type.
- `DSC_TYPE_UINT`: Unsigned integer type.
- `DSC_TYPE_LONG`: Long integer type.
- `DSC_TYPE_ULONG`: Unsigned long integer type.
- `DSC_TYPE_LLONG`: Long long integer type.
- `DSC_TYPE_ULLONG`: Unsigned long long integer type.
- `DSC_TYPE_FLOAT`: Single-precision floating-point type.
- `DSC_TYPE_DOUBLE`: Double-precision floating-point type.
- `DSC_TYPE_LDOUBLE`: Long double-precision floating-point type.
- `DSC_TYPE_STRING`: String type (character pointer).
- `DSC_TYPE_BOOL`: Boolean type.


These constants can be used to specify the type of elements stored in the containers provided by the DSC library.

## dsc_type_of Function

The `dsc_type_of` function is used to determine the type of a given data pointer. It takes a void pointer to the data and attempts to determine its type based on the size of the dereferenced pointer. The function compares the size of the dereferenced pointer with the sizes of known types defined in the `DSCType` enum and returns the corresponding `DSCType` value if a match is found. If no match is found, it returns `DSC_TYPE_UNKNOWN`.

The function signature is as follows:

```c
DSCType dsc_type_of(void *data);
```

- `data`: Pointer to the data.
- Returns: The `DSCType` value representing the type of the data, or `DSC_TYPE_UNKNOWN` if the type cannot be determined.

Note: The `dsc_type_of` function assumes that the data pointer is a valid pointer to the actual data. If the pointer is invalid or points to a different type than the one stored in the container, the behavior is undefined. It is the caller's responsibility to ensure that the data pointer is valid and points to the correct type.

## Usage Example

Here's an example of how to use the `DSCType` enum and the `dsc_type_of` function:

```c
int value = 42;
void *data = &value;

DSCType type = dsc_type_of(data);

if (type == DSC_TYPE_INT) {
    printf("The data is of type int.\n");
} else {
    printf("The data is of unknown type.\n");
}
```

In this example, we declare an integer variable `value` and obtain a void pointer `data` to its address. We then use the `dsc_type_of` function to determine the type of the data pointed to by `data`. If the type matches `DSC_TYPE_INT`, we print a message indicating that the data is of type int. Otherwise, we print a message indicating that the data is of unknown type.

## Conclusion

The DSC type system provides a way to handle different data types in generic containers. By using the `DSCType` enum and the `dsc_type_of` function, you can specify and determine the types of elements stored in the containers. However, it's important to ensure that the data pointers passed to the containers and the `dsc_type_of` function are valid and point to the correct types to avoid undefined behavior.
