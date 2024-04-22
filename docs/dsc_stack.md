# Stack

A stack is a linear data structure that follows the Last-In-First-Out (LIFO) principle. It provides operations to push elements onto the top of the stack and pop elements from the top of the stack.

## Data Structures

### `dsc_stack_t`

```c
struct dsc_stack_t;
```

Represents a stack. The internal implementation of the `dsc_stack_t` struct is hidden and defined in the source file.

## Functions

### `dsc_stack_create`

```c
dsc_stack_t *dsc_stack_create();
```

Creates a new empty stack.

**Returns:** A pointer to the newly created stack, or `NULL` if memory allocation fails.

**Example:**

```c
dsc_stack_t *stack = dsc_stack_create();
if (stack == NULL) {
    // Handle memory allocation failure
}
```

### `dsc_stack_free`

```c
void dsc_stack_free(dsc_stack_t *stack);
```

Destroys the stack and frees its memory.

**Parameters:**
- `stack`: The stack to destroy.

**Example:**

```c
dsc_stack_t *stack = dsc_stack_create();
// Use the stack
dsc_stack_free(stack);
```

### `dsc_stack_push`

```c
void dsc_stack_push(dsc_stack_t *stack, int value);
```

Pushes an element onto the top of the stack.

**Parameters:**
- `stack`: The stack to push the element onto.
- `value`: The value to push.

**Example:**

```c
dsc_stack_t *stack = dsc_stack_create();
dsc_stack_push(stack, 42);
dsc_stack_push(stack, 73);
```

### `dsc_stack_pop`

```c
void dsc_stack_pop(dsc_stack_t *stack);
```

Removes the top element from the stack.

**Parameters:**
- `stack`: The stack to pop from.

**Example:**

```c
dsc_stack_t *stack = dsc_stack_create();
dsc_stack_push(stack, 42);
dsc_stack_push(stack, 73);
int top_value = dsc_stack_top(stack); // top_value = 73
dsc_stack_pop(stack); // Removes 73 from the stack
```

### `dsc_stack_top`

```c
int dsc_stack_top(const dsc_stack_t *stack);
```

Retrieves the value of the top element on the stack without removing it.

**Parameters:**
- `stack`: The stack to get the top element from.

**Returns:** The value of the top element.

**Example:**

```c
dsc_stack_t *stack = dsc_stack_create();
dsc_stack_push(stack, 42);
dsc_stack_push(stack, 73);
int top_value = dsc_stack_top(stack); // top_value = 73
```

### `dsc_stack_empty`

```c
bool dsc_stack_empty(const dsc_stack_t *stack);
```

Checks if the stack is empty.

**Parameters:**
- `stack`: The stack to check.

**Returns:** `true` if the stack is empty, `false` otherwise.

**Example:**

```c
dsc_stack_t *stack = dsc_stack_create();
if (dsc_stack_empty(stack)) {
    printf("The stack is empty\n");
} else {
    printf("The stack is not empty\n");
}
```

### `dsc_stack_size`

```c
unsigned int dsc_stack_size(const dsc_stack_t *stack);
```

Gets the number of elements in the stack.

**Parameters:**
- `stack`: The stack to get the size of.

**Returns:** The number of elements in the stack.

**Example:**

```c
dsc_stack_t *stack = dsc_stack_create();
dsc_stack_push(stack, 42);
dsc_stack_push(stack, 73);
unsigned int size = dsc_stack_size(stack); // size = 2
```
