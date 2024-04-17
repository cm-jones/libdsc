# Singly Linked List

The singly linked list is a linear data structure in which the elements are not stored at contiguous memory locations. It consists of a sequence of nodes, where each node contains a value and a pointer to the next node in the sequence.

## Data Structures

### `dsc_node_t`

`dsc_node_t` represents a node in the list. The internal structure of `dsc_node_t` is not exposed to the library user.

### `dsc_list_t`

`dsc_list_t` represents a singly linked list. The internal structure of `dsc_list_t` is not exposed to the library user.

## Functions

### `dsc_list_create`

```c
struct dsc_list_t *dsc_list_create();
```

Creates a new empty list.

**Returns:** A pointer to the newly created list, or `NULL` if memory allocation fails.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
if (list == NULL) {
    // Handle memory allocation failure
}
```

### `dsc_list_destroy`

```c
void dsc_list_destroy(dsc_list_t *list);
```

Destroys the list and frees its memory.

**Parameters:**
- `list`: The list to destroy.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
// Use the list
dsc_list_destroy(list);
```

### `dsc_list_push_front`

```c
void dsc_list_push_front(dsc_list_t *list, int value);
```

Inserts a value at the beginning of the list.

**Parameters:**
- `list`: The list to insert the value into.
- `value`: The value to insert.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
dsc_list_push_front(list, 42);
dsc_list_push_front(list, 73);
```

### `dsc_list_insert_after`

```c
void dsc_list_insert_after(dsc_list_t *list, dsc_node_t *prev_node, int value);
```

Inserts a value after a specific node in the list.

**Parameters:**
- `list`: The list to insert the value into.
- `prev_node`: The node after which to insert the value.
- `value`: The value to insert.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
dsc_list_push_front(list, 42);
dsc_node_t *node = dsc_list_get_head(list);
dsc_list_insert_after(list, node, 73);
```

### `dsc_list_pop_front`

```c
void dsc_list_pop_front(dsc_list_t *list);
```

Removes the first node from the list.

**Parameters:**
- `list`: The list to remove the first node from.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
dsc_list_push_front(list, 42);
dsc_list_push_front(list, 73);
dsc_list_pop_front(list); // Removes 73 from the list
```

### `dsc_list_remove`

```c
void dsc_list_remove(dsc_list_t *list, int value);
```

Removes the first occurrence of a value from the list.

**Parameters:**
- `list`: The list to remove the value from.
- `value`: The value to remove.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
dsc_list_push_front(list, 42);
dsc_list_push_front(list, 73);
dsc_list_remove(list, 73); // Removes the first occurrence of 73
```

### `dsc_list_remove_all`

```c
void dsc_list_remove_all(dsc_list_t *list, int value);
```

Removes all occurrences of a value from the list.

**Parameters:**
- `list`: The list to remove the values from.
- `value`: The value to remove.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
dsc_list_push_front(list, 42);
dsc_list_push_front(list, 73);
dsc_list_push_front(list, 73);
dsc_list_remove_all(list, 73); // Removes all occurrences of 73
```

### `dsc_list_front`

```c
int dsc_list_front(const dsc_list_t *list);
```

Retrieves the value of the first element in the list.

**Parameters:**
- `list`: The list to get the front element from.

**Returns:** The value of the front element, or 0 if the list is empty or `NULL`.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
dsc_list_push_front(list, 42);
dsc_list_push_front(list, 73);
int front_value = dsc_list_front(list); // front_value = 73
```

### `dsc_list_empty`

```c
bool dsc_list_empty(const dsc_list_t *list);
```

Checks if the list is empty.

**Parameters:**
- `list`: The list to check.

**Returns:** `true` if the list is empty or `NULL`, `false` otherwise.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
if (dsc_list_empty(list)) {
    printf("The list is empty\n");
} else {
    printf("The list is not empty\n");
}
```

### `dsc_list_print`

```c
void dsc_list_print(const dsc_list_t *list);
```

Prints the values of the list.

**Parameters:**
- `list`: The list to print.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
dsc_list_push_front(list, 42);
dsc_list_push_front(list, 73);
dsc_list_print(list); // Prints "73 42"
```

### `dsc_list_get_head`

```c
dsc_node_t *dsc_list_get_head(const dsc_list_t *list);
```

Gets the head node of the list.

**Parameters:**
- `list`: The list to get the head from.

**Returns:** A pointer to the head node of the list, or `NULL` if the list is empty or `NULL`.

**Example:**

```c
dsc_list_t *list = dsc_list_create();
dsc_list_push_front(list, 42);
dsc_node_t *head = dsc_list_get_head(list);
// Use the head node
```
