# DSC Error Handling

The DSC library provides error handling mechanisms to help users identify and handle errors that may occur during the usage of the library. This document describes the error handling approach and the available error codes.

## Error Handling Approach

The DSC library functions return error codes to indicate the success or failure of an operation. The error codes are defined in the `dsc_error.h` header file.

When a function encounters an error, it sets the error code using the appropriate error constant from the `DSCError` enum and returns an appropriate value (e.g., NULL, false, or an invalid value) to indicate the failure. The user can then check the return value and handle the error accordingly.

It is the responsibility of the user to check the return values of the library functions and handle the errors appropriately based on their specific use case and requirements.

## Error Codes

The following error codes are defined in the `dsc_error.h` header file:

- `DSC_ERROR_OK`: No error occurred. The operation was successful.
- `DSC_ERROR_TYPE_MISMATCH`: There was a mismatch between the expected type and the actual type of the data.
- `DSC_ERROR_INVALID_ARGUMENT`: An invalid argument was passed to a function.
- `DSC_ERROR_OUT_OF_RANGE`: The specified index or position is out of the valid range.
- `DSC_ERROR_OUT_OF_MEMORY`: Memory allocation failed.
- `DSC_ERROR_EMPTY_CONTAINER`: The container is empty.
- `DSC_ERROR_KEY_NOT_FOUND`: The specified key was not found in the container.
- `DSC_ERROR_HASHMAP_KEY_ALREADY_EXISTS`: The specified key already exists in the hashmap.

These error codes provide a way to identify and handle specific error conditions that may occur while using the DSC library.

## Error Handling Example

Here's an example of how to handle errors when using the DSC library:

```c
#include <stdio.h>
#include "dsc_list.h"
#include "dsc_error.h"

int main() {
    DSCList list = dsc_list_init(DSC_TYPE_INT);
    if (list == NULL) {
        fprintf(stderr, "Failed to initialize the list.\n");
        return 1;
    }

    // Perform operations on the list
    // ...

    // Check for errors
    if (dsc_error(list) != DSC_ERROR_OK) {
        fprintf(stderr, "An error occurred. Error code: %d\n", dsc_error(list));
        // Handle the error appropriately
    }

    dsc_list_deinit(list);

    return 0;
}
```

In this example, we initialize a list using `dsc_list_init`. If the initialization fails, we print an error message.

After performing operations on the list, we check for errors using the `dsc_error` function, which takes the list as an argument and returns the last error code. If an error occurred (i.e., the error code is not `DSC_ERROR_OK`), we print the error code and handle the error appropriately.

Finally, we deinitialize the list using `dsc_list_deinit` to clean up the resources.

## Conclusion

Error handling is an important aspect of using the DSC library. By leveraging the provided error codes and checking the return values of the library functions, users can detect and handle errors effectively, ensuring the stability and reliability of their programs.

Remember to always check the return values of the library functions and handle errors appropriately based on your specific use case and requirements.
