# Hash Map

A hash map is an implementation of the associative array data structure, which provides constant-time average performance for insertion, deletion, and lookup operations. It associates keys with values and allows for efficient retrieval and modification of the associated values based on their keys.

## Data Structures

### `dsc_map_t`

```c
struct dsc_map_t;
```

Represents a hash map. The internal implementation of the `dsc_map_t` struct is hidden and defined in the source file.

## Functions

### `dsc_map_create`

```c
dsc_map_t *dsc_map_create();
```

Creates a new empty map.

**Returns:** A pointer to the newly created map, or `NULL` if memory allocation fails.

**Example:**

```c
dsc_map_t *map = dsc_map_create();
if (map == NULL) {
    // Handle memory allocation failure
}
```

### `dsc_map_free`

```c
void dsc_map_free(dsc_map_t *map);
```

Destroys the map and frees its memory.

**Parameters:**
- `map`: The map to destroy.

**Example:**

```c
dsc_map_t *map = dsc_map_create();
// Use the map
dsc_map_free(map);
```

### `dsc_map_insert`

```c
bool dsc_map_insert(dsc_map_t *map, int key, int value);
```

Inserts a key-value pair into the map.

**Parameters:**
- `map`: The map to insert the key-value pair into.
- `key`: The key to insert.
- `value`: The value to associate with the key.

**Returns:** `true` if the key-value pair was inserted successfully, `false` if the key already exists.

**Example:**

```c
dsc_map_t *map = dsc_map_create();
int key = 42;
int value = 73;
if (dsc_map_insert(map, key, value)) {
    printf("Key-value pair inserted successfully\n");
} else {
    printf("Key already exists\n");
}
```

### `dsc_map_erase`

```c
bool dsc_map_erase(dsc_map_t *map, int key);
```

Erases the key-value pair with the given key from the map.

**Parameters:**
- `map`: The map to erase the key-value pair from.
- `key`: The key to erase.

**Returns:** `true` if the key-value pair was erased successfully, `false` if the key was not found.

**Example:**

```c
dsc_map_t *map = dsc_map_create();
int key = 42;
dsc_map_insert(map, key, 73);
if (dsc_map_erase(map, key)) {
    printf("Key-value pair erased successfully\n");
} else {
    printf("Key not found\n");
}
```

### `dsc_map_get`

```c
int dsc_map_get(const dsc_map_t *map, int key);
```

Retrieves the value associated with the given key.

**Parameters:**
- `map`: The map to retrieve the value from.
- `key`: The key to retrieve the value for.

**Returns:** The value associated with the key, or 0 if the key is not found.

**Example:**

```c
dsc_map_t *map = dsc_map_create();
int key = 42;
dsc_map_insert(map, key, 73);
int value = dsc_map_get(map, key); // value = 73
```

### `dsc_map_contains`

```c
bool dsc_map_contains(const dsc_map_t *map, int key);
```

Checks if the map contains the given key.

**Parameters:**
- `map`: The map to check.
- `key`: The key to check for.

**Returns:** `true` if the key exists in the map, `false` otherwise.

**Example:**

```c
dsc_map_t *map = dsc_map_create();
int key = 42;
dsc_map_insert(map, key, 73);
if (dsc_map_contains(map, key)) {
    printf("Key exists in the map\n");
} else {
    printf("Key does not exist in the map\n");
}
```

### `dsc_map_size`

```c
unsigned int dsc_map_size(const dsc_map_t *map);
```

Gets the number of key-value pairs in the map.

**Parameters:**
- `map`: The map to get the size of.

**Returns:** The number of key-value pairs in the map.

**Example:**

```c
dsc_map_t *map = dsc_map_create();
dsc_map_insert(map, 42, 73);
dsc_map_insert(map, 54, 21);
unsigned int size = dsc_map_size(map); // size = 2
```

### `dsc_map_empty`

```c
bool dsc_map_empty(const dsc_map_t *map);
```

Checks if the map is empty.

**Parameters:**
- `map`: The map to check.

**Returns:** `true` if the map is empty, `false` otherwise.

**Example:**

```c
dsc_map_t *map = dsc_map_create();
if (dsc_map_empty(map)) {
    printf("The map is empty\n");
} else {
    printf("The map is not empty\n");
}
```

### `dsc_map_clear`

```c
void dsc_map_clear(dsc_map_t *map);
```

Clears all key-value pairs from the map.

**Parameters:**
- `map`: The map to clear.

**Example:**

```c
dsc_map_t *map = dsc_map_create();
dsc_map_insert(map, 42, 73);
dsc_map_insert(map, 54, 21);
dsc_map_clear(map);
// The map is now empty
```
