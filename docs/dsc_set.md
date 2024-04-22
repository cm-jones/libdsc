# Hash Set

A hash set is an implementation of the set data structure using a hash table. It provides constant-time average performance for insertion, deletion, and lookup operations.

## Data Structures

### `dsc_set_entry_t`

```c
struct dsc_set_entry_t {
    int key;
    struct dsc_set_entry_t *next;
};
```

Represents an entry in the hash set.

- `key`: The key of the entry.
- `next`: Pointer to the next entry in case of collisions.

### `DSCSet`

```c
struct DSCSet {
    struct dsc_set_entry_t **buckets;
    int capacity;
    int size;
};
```

Represents a hash set.

- `buckets`: Array of pointers to entries.
- `capacity`: The current capacity of the hash set.
- `size`: The number of elements in the hash set.

## Functions

### `dsc_set_create`

```c
DSCSet *dsc_set_create();
```

Creates a new hash set.

**Returns:** A pointer to the newly created hash set, or `NULL` if memory allocation fails.

**Example:**

```c
DSCSet *set = dsc_set_create();
if (set == NULL) {
    // Handle memory allocation failure
}
```

### `dsc_set_free`

```c
void dsc_set_free(DSCSet *set);
```

Destroys the hash set and frees its memory.

**Parameters:**
- `set`: The hash set to destroy.

**Example:**

```c
DSCSet *set = dsc_set_create();
// Use the set
dsc_set_free(set);
```

### `dsc_set_insert`

```c
bool dsc_set_insert(DSCSet *set, int value);
```

Inserts an element into the hash set.

**Parameters:**
- `set`: The hash set to insert the element into.
- `value`: The value to insert.

**Returns:** `true` if the element was inserted successfully, `false` if the element already exists.

**Example:**

```c
DSCSet *set = dsc_set_create();
int value = 42;
if (dsc_set_insert(set, value)) {
    printf("Value %d inserted successfully\n", value);
} else {
    printf("Value %d already exists\n", value);
}
```

### `dsc_set_erase`

```c
bool dsc_set_erase(DSCSet *set, int value);
```

Erases an element from the hash set.

**Parameters:**
- `set`: The hash set to erase the element from.
- `value`: The value to erase.

**Returns:** `true` if the element was erased successfully, `false` if the element was not found.

**Example:**

```c
DSCSet *set = dsc_set_create();
int value = 42;
dsc_set_insert(set, value);
if (dsc_set_erase(set, value)) {
    printf("Value %d erased successfully\n", value);
} else {
    printf("Value %d not found\n", value);
}
```

### `dsc_set_contains`

```c
bool dsc_set_contains(const DSCSet *set, int value);
```

Checks if an element exists in the hash set.

**Parameters:**
- `set`: The hash set to check.
- `value`: The value to check for.

**Returns:** `true` if the element exists, `false` otherwise.

**Example:**

```c
DSCSet *set = dsc_set_create();
int value = 42;
dsc_set_insert(set, value);
if (dsc_set_contains(set, value)) {
    printf("Value %d exists in the set\n", value);
} else {
    printf("Value %d does not exist in the set\n", value);
}
```

### `dsc_set_size`

```c
unsigned int dsc_set_size(const DSCSet *set);
```

Gets the size of the hash set.

**Parameters:**
- `set`: The hash set to get the size of.

**Returns:** The size of the hash set.

**Example:**

```c
DSCSet *set = dsc_set_create();
dsc_set_insert(set, 42);
dsc_set_insert(set, 73);
unsigned int size = dsc_set_size(set);
printf("Size of the set: %zu\n", size);
```

### `dsc_set_empty`

```c
bool dsc_set_empty(const DSCSet *set);
```

Checks if the hash set is empty.

**Parameters:**
- `set`: The hash set to check.

**Returns:** `true` if the hash set is empty, `false` otherwise.

**Example:**

```c
DSCSet *set = dsc_set_create();
if (dsc_set_empty(set)) {
    printf("The set is empty\n");
} else {
    printf("The set is not empty\n");
}
```

### `dsc_set_clear`

```c
void dsc_set_clear(DSCSet *set);
```

Clears all elements from the hash set.

**Parameters:**
- `set`: The hash set to clear.

**Example:**

```c
DSCSet *set = dsc_set_create();
dsc_set_insert(set, 42);
dsc_set_insert(set, 73);
dsc_set_clear(set);
// The set is now empty
```
