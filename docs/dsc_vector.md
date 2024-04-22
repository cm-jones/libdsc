# Vector

A vector is a dynamic array data structure that provides flexible storage and efficient insertion and deletion of elements. It automatically manages memory allocation and deallocation, allowing the vector to grow and shrink as needed.

## Data Structures

### `dsc_vector_t`

```c
struct dsc_vector_t;
```

Represents a vector. The internal implementation of the `dsc_vector_t` struct is hidden and defined in the source file.

## Functions

### `dsc_vector_create`

```c
dsc_vector_t *dsc_vector_create();
```

Creates a new empty vector.

**Returns:** A pointer to the newly created vector, or `NULL` if memory allocation fails.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
if (vector == NULL) {
    // Handle memory allocation failure
}
```

### `dsc_vector_free`

```c
void dsc_vector_free(dsc_vector_t *vector);
```

Destroys the vector and frees its memory.

**Parameters:**
- `vector`: The vector to destroy.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
// Use the vector
dsc_vector_free(vector);
```

### `dsc_vector_push_back`

```c
void dsc_vector_push_back(dsc_vector_t *vector, int value);
```

Inserts an element at the end of the vector.

**Parameters:**
- `vector`: The vector to push the element into.
- `value`: The value to push.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
dsc_vector_push_back(vector, 42);
dsc_vector_push_back(vector, 73);
```

### `dsc_vector_pop_back`

```c
void dsc_vector_pop_back(dsc_vector_t *vector);
```

Removes the last element from the vector.

**Parameters:**
- `vector`: The vector to pop from.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
dsc_vector_push_back(vector, 42);
dsc_vector_push_back(vector, 73);
dsc_vector_pop_back(vector); // Removes 73 from the vector
```

### `dsc_vector_insert`

```c
void dsc_vector_insert(dsc_vector_t *vector, int value);
```

Inserts an element at the beginning of the vector.

**Parameters:**
- `vector`: The vector to insert the element into.
- `value`: The value to insert.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
dsc_vector_insert(vector, 42);
dsc_vector_insert(vector, 73);
```

### `dsc_vector_erase`

```c
void dsc_vector_erase(dsc_vector_t *vector);
```

Removes the first element from the vector.

**Parameters:**
- `vector`: The vector to remove the first element from.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
dsc_vector_insert(vector, 42);
dsc_vector_insert(vector, 73);
dsc_vector_erase(vector); // Removes 42 from the vector
```

### `dsc_vector_at`

```c
int dsc_vector_at(const dsc_vector_t *vector, unsigned int index);
```

Retrieves the value of the element at the specified index.

**Parameters:**
- `vector`: The vector to get the element from.
- `index`: The index of the element to retrieve.

**Returns:** The value of the element at the specified index, or 0 if the index is out of bounds.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
dsc_vector_push_back(vector, 42);
dsc_vector_push_back(vector, 73);
int value = dsc_vector_at(vector, 1); // value = 73
```

### `dsc_vector_empty`

```c
bool dsc_vector_empty(const dsc_vector_t *vector);
```

Checks if the vector is empty.

**Parameters:**
- `vector`: The vector to check.

**Returns:** `true` if the vector is empty, `false` otherwise.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
if (dsc_vector_empty(vector)) {
    printf("The vector is empty\n");
} else {
    printf("The vector is not empty\n");
}
```

### `dsc_vector_size`

```c
unsigned int dsc_vector_size(const dsc_vector_t *vector);
```

Gets the number of elements in the vector.

**Parameters:**
- `vector`: The vector to get the size of.

**Returns:** The number of elements in the vector.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
dsc_vector_push_back(vector, 42);
dsc_vector_push_back(vector, 73);
unsigned int size = dsc_vector_size(vector); // size = 2
```

### `dsc_vector_capacity`

```c
unsigned int dsc_vector_capacity(const dsc_vector_t *vector);
```

Gets the maximum number of elements the vector can hold before needing to allocate more memory.

**Parameters:**
- `vector`: The vector to get the capacity of.

**Returns:** The maximum number of elements the vector can hold.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
dsc_vector_push_back(vector, 42);
dsc_vector_push_back(vector, 73);
unsigned int capacity = dsc_vector_capacity(vector); // capacity = 2 (or more, depending on the initial capacity)
```

### `dsc_vector_reserve`

```c
void dsc_vector_reserve(dsc_vector_t *vector, unsigned int new_capacity);
```

Reserves memory for the vector to hold at least the specified number of elements.

**Parameters:**
- `vector`: The vector to reserve memory for.
- `new_capacity`: The minimum capacity to reserve.

**Example:**

```c
dsc_vector_t *vector = dsc_vector_create();
dsc_vector_reserve(vector, 10); // Reserve memory for at least 10 elements
```
