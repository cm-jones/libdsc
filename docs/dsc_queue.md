# Queue

A queue is a linear data structure that follows the First-In-First-Out (FIFO) principle. It provides operations to insert elements at the back and remove elements from the front.

## Data Structures

### `dsc_queue_t`

```c
struct dsc_queue_t;
```

Represents a queue. The internal implementation of the `dsc_queue_t` struct is hidden and defined in the source file.

## Functions

### `dsc_queue_create`

```c
dsc_queue_t *dsc_queue_create();
```

Creates a new empty queue.

**Returns:** A pointer to the newly created queue, or `NULL` if memory allocation fails.

**Example:**

```c
dsc_queue_t *queue = dsc_queue_create();
if (queue == NULL) {
    // Handle memory allocation failure
}
```

### `dsc_queue_free`

```c
void dsc_queue_free(dsc_queue_t *queue);
```

Destroys the queue and frees its memory.

**Parameters:**
- `queue`: The queue to destroy.

**Example:**

```c
dsc_queue_t *queue = dsc_queue_create();
// Use the queue
dsc_queue_free(queue);
```

### `dsc_queue_push`

```c
void dsc_queue_push(dsc_queue_t *queue, int value);
```

Inserts an element at the end of the queue.

**Parameters:**
- `queue`: The queue to push the element into.
- `value`: The value to push.

**Example:**

```c
dsc_queue_t *queue = dsc_queue_create();
dsc_queue_push(queue, 42);
dsc_queue_push(queue, 73);
```

### `dsc_queue_pop`

```c
void dsc_queue_pop(dsc_queue_t *queue);
```

Removes the element at the front of the queue.

**Parameters:**
- `queue`: The queue to pop from.

**Example:**

```c
dsc_queue_t *queue = dsc_queue_create();
dsc_queue_push(queue, 42);
dsc_queue_push(queue, 73);
int front_value = dsc_queue_front(queue); // front_value = 42
dsc_queue_pop(queue); // Removes 42 from the queue
```

### `dsc_queue_front`

```c
int dsc_queue_front(const dsc_queue_t *queue);
```

Retrieves the value of the element at the front of the queue without removing it.

**Parameters:**
- `queue`: The queue to get the front element from.

**Returns:** The value of the front element.

**Example:**

```c
dsc_queue_t *queue = dsc_queue_create();
dsc_queue_push(queue, 42);
dsc_queue_push(queue, 73);
int front_value = dsc_queue_front(queue); // front_value = 42
```

### `dsc_queue_back`

```c
int dsc_queue_back(const dsc_queue_t *queue);
```

Retrieves the value of the element at the back of the queue without removing it.

**Parameters:**
- `queue`: The queue to get the back element from.

**Returns:** The value of the back element.

**Example:**

```c
dsc_queue_t *queue = dsc_queue_create();
dsc_queue_push(queue, 42);
dsc_queue_push(queue, 73);
int back_value = dsc_queue_back(queue); // back_value = 73
```

### `dsc_queue_empty`

```c
bool dsc_queue_empty(const dsc_queue_t *queue);
```

Checks if the queue is empty.

**Parameters:**
- `queue`: The queue to check.

**Returns:** `true` if the queue is empty, `false` otherwise.

**Example:**

```c
dsc_queue_t *queue = dsc_queue_create();
if (dsc_queue_empty(queue)) {
    printf("The queue is empty\n");
} else {
    printf("The queue is not empty\n");
}
```

### `dsc_queue_size`

```c
unsigned int dsc_queue_size(const dsc_queue_t *queue);
```

Gets the number of elements in the queue.

**Parameters:**
- `queue`: The queue to get the size of.

**Returns:** The number of elements in the queue.

**Example:**

```c
dsc_queue_t *queue = dsc_queue_create();
dsc_queue_push(queue, 42);
dsc_queue_push(queue, 73);
unsigned int size = dsc_queue_size(queue); // size = 2
```
