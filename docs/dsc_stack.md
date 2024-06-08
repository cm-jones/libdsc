# Stack

A stack is a linear data structure that follows the Last-In-First-Out (LIFO) principle. It provides operations to push elements onto the top of the stack and pop elements from the top of the stack.

## Data Structures

### `DSCStack`

```c
struct DSCStack;
```

Represents a stack. The internal implementation of the `DSCStack` struct is hidden and defined in the source file.

## Functions

### `dsc_stack_init`

```c
DSCError dsc_stack_init(DSCStack *new_stack, DSCType type);
```

Creates a new empty stack.

**Returns:** A pointer to the newly created stack, or `NULL` if memory allocation fails.

**Example:**

```c
DSCStack *stack;
DSCError error = dsc_stack_init(stack, DSC_TYPE_INT);
if (error != DSC_ERROR_OK) {
    // Handle error
}
```

### `dsc_stack_deinit`

```c
DSCError dsc_stack_deinit(DSCStack *stack);
```

Destroys the stack and frees its memory.

**Parameters:**
- `stack`: The stack to destroy.

**Example:**

```c
DSCStack *stack;
dsc_stack_init(stack, DSC_TYPE_INT);
// Use the stack
dsc_stack_free(stack);
```

### `dsc_stack_push`

```c
void dsc_stack_push(DSCStack *stack, int value);
```

Pushes an element onto the top of the stack.

**Parameters:**
- `stack`: The stack to push the element onto.
- `value`: The value to push.

**Example:**

```c
DSCStack *stack = dsc_stack_create();
dsc_stack_push(stack, 42);
dsc_stack_push(stack, 73);
```

### `dsc_stack_pop`

```c
void dsc_stack_pop(DSCStack *stack);
```

Removes the top element from the stack.

**Parameters:**
- `stack`: The stack to pop from.

**Example:**

```c
DSCStack *stack = dsc_stack_create();
dsc_stack_push(stack, 42);
dsc_stack_push(stack, 73);
int top_value = DSCStackop(stack); // top_value = 73
dsc_stack_pop(stack); // Removes 73 from the stack
```

### `DSCStackop`

```c
int DSCStackop(const DSCStack *stack);
```

Retrieves the value of the top element on the stack without removing it.

**Parameters:**
- `stack`: The stack to get the top element from.

**Returns:** The value of the top element.

**Example:**

```c
DSCStack *stack = dsc_stack_create();
dsc_stack_push(stack, 42);
dsc_stack_push(stack, 73);
int top_value = DSCStackop(stack); // top_value = 73
```

### `dsc_stack_empty`

```c
bool dsc_stack_empty(const DSCStack *stack);
```

Checks if the stack is empty.

**Parameters:**
- `stack`: The stack to check.

**Returns:** `true` if the stack is empty, `false` otherwise.

**Example:**

```c
DSCStack *stack = dsc_stack_create();
if (dsc_stack_empty(stack)) {
    printf("The stack is empty\n");
} else {
    printf("The stack is not empty\n");
}
```

### `dsc_stack_size`

```c
unsigned int dsc_stack_size(const DSCStack *stack);
```

Gets the number of elements in the stack.

**Parameters:**
- `stack`: The stack to get the size of.

**Returns:** The number of elements in the stack.

**Example:**

```c
DSCStack *stack = dsc_stack_create();
dsc_stack_push(stack, 42);
dsc_stack_push(stack, 73);
unsigned int size = dsc_stack_size(stack); // size = 2
```
