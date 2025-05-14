#include <benchmark/benchmark.h>

#include <stack>

#include "libdsc/stack.h"

// Benchmark size operation
static void BM_StackSize(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));
    int value = 42;
    for (size_t i = 0; i < 1000; ++i) {
        stack_push(stack, &value);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(stack_size(stack));
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackSize)->Range(1 << 10, 1 << 20);

// Benchmark std::stack size
static void BM_StdStackSize(benchmark::State &state) {
    std::stack<int> stack;
    for (size_t i = 0; i < 1000; ++i) {
        stack.push(42);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(stack.size());
    }
}
BENCHMARK(BM_StdStackSize)->Range(1 << 10, 1 << 20);

// Benchmark empty check
static void BM_StackEmpty(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));

    for (auto _ : state) {
        benchmark::DoNotOptimize(stack_empty(stack));
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackEmpty)->Range(1 << 10, 1 << 20);

// Benchmark std::stack empty
static void BM_StdStackEmpty(benchmark::State &state) {
    std::stack<int> stack;

    for (auto _ : state) {
        benchmark::DoNotOptimize(stack.empty());
    }
}
BENCHMARK(BM_StdStackEmpty)->Range(1 << 10, 1 << 20);

// Benchmark clear operation
static void BM_StackClear(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));
    int value = 42;

    for (auto _ : state) {
        state.PauseTiming();
        // Fill stack
        for (size_t i = 0; i < state.range(0); ++i) {
            stack_push(stack, &value);
        }
        state.ResumeTiming();

        stack_clear(stack);
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackClear)->Range(1 << 10, 1 << 20);

// Benchmark std::stack clear equivalent
static void BM_StdStackClear(benchmark::State &state) {
    std::stack<int> stack;

    for (auto _ : state) {
        state.PauseTiming();
        // Fill stack
        for (size_t i = 0; i < state.range(0); ++i) {
            stack.push(42);
        }
        state.ResumeTiming();

        while (!stack.empty()) {
            stack.pop();
        }
    }
}
BENCHMARK(BM_StdStackClear)->Range(1 << 10, 1 << 20);

// Benchmark reserve operation
static void BM_StackReserve(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));

    for (auto _ : state) {
        benchmark::DoNotOptimize(stack_reserve(stack, state.range(0)));
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackReserve)->Range(1 << 10, 1 << 20);

// Benchmark push
static void BM_StackPush(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));

    for (auto _ : state) {
        int value = 42;
        benchmark::DoNotOptimize(stack_push(stack, &value));
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackPush)->Range(1, 1 << 20);

// Benchmark std::stack push
static void BM_StdStackPush(benchmark::State &state) {
    std::stack<int> stack;

    for (auto _ : state) {
        stack.push(42);
        benchmark::DoNotOptimize(stack);
    }
}
BENCHMARK(BM_StdStackPush)->Range(1, 1 << 20);

// Benchmark push and pop
static void BM_StackPushPop(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));

    for (auto _ : state) {
        int value = 42;
        stack_push(stack, &value);
        stack_pop(stack);
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackPushPop)->Range(1, 1 << 20);

// Benchmark std::stack push and pop
static void BM_StdStackPushPop(benchmark::State &state) {
    std::stack<int> stack;

    for (auto _ : state) {
        stack.push(42);
        stack.pop();
    }
}
BENCHMARK(BM_StdStackPushPop)->Range(1, 1 << 20);

// Benchmark top access
static void BM_StackTop(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));
    int value = 42;
    stack_push(stack, &value);

    for (auto _ : state) {
        benchmark::DoNotOptimize(dsc_stack_top(stack));
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackTop)->Range(1 << 10, 1 << 20);

// Benchmark std::stack top access
static void BM_StdStackTop(benchmark::State &state) {
    std::stack<int> stack;
    stack.push(42);

    for (auto _ : state) {
        benchmark::DoNotOptimize(stack.top());
    }
}
BENCHMARK(BM_StdStackTop)->Range(1 << 10, 1 << 20);

// Benchmark push with pre-reserved capacity
static void BM_StackPushReserved(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));
    stack_reserve(stack, state.range(0));
    int value = 42;

    for (auto _ : state) {
        state.PauseTiming();
        stack_clear(stack);
        state.ResumeTiming();

        for (size_t i = 0; i < state.range(0); ++i) {
            stack_push(stack, &value);
        }
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackPushReserved)->Range(1 << 10, 1 << 20);

// Benchmark std::stack push with pre-reserved vector
static void BM_StdStackPushReserved(benchmark::State &state) {
    std::vector<int> vec;
    vec.reserve(state.range(0));
    std::stack<int, std::vector<int>> stack(vec);

    for (auto _ : state) {
        state.PauseTiming();
        while (!stack.empty()) stack.pop();
        state.ResumeTiming();

        for (size_t i = 0; i < state.range(0); ++i) {
            stack.push(42);
        }
    }
}
BENCHMARK(BM_StdStackPushReserved)->Range(1 << 10, 1 << 20);

// Benchmark alternating push/pop pattern
static void BM_StackAlternating(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));
    stack_reserve(stack, state.range(0) / 2);  // Reserve half capacity
    int value = 42;
    bool push = true;

    for (auto _ : state) {
        if (push) {
            benchmark::DoNotOptimize(stack_push(stack, &value));
        } else {
            if (!stack_empty(stack)) {
                benchmark::DoNotOptimize(stack_pop(stack));
            }
        }
        push = !push;
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackAlternating)->Range(1 << 10, 1 << 20);

// Benchmark std::stack alternating push/pop
static void BM_StdStackAlternating(benchmark::State &state) {
    std::stack<int> stack;
    bool push = true;

    for (auto _ : state) {
        if (push) {
            stack.push(42);
            benchmark::DoNotOptimize(stack);
        } else {
            if (!stack.empty()) {
                stack.pop();
                benchmark::DoNotOptimize(stack);
            }
        }
        push = !push;
    }
}
BENCHMARK(BM_StdStackAlternating)->Range(1 << 10, 1 << 20);

// Benchmark reserve with different growth patterns
static void BM_StackReserveGrowth(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));

    for (auto _ : state) {
        stack_reserve(stack, state.range(0));
        benchmark::DoNotOptimize(stack);
        state.PauseTiming();
        stack_clear(stack);
        state.ResumeTiming();
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackReserveGrowth)->RangeMultiplier(2)->Range(1 << 10, 1 << 20);

// Benchmark push performance at different stack sizes
static void BM_StackPushSized(benchmark::State &state) {
    dsc_stack_t *stack = stack_create(sizeof(int));
    int value = 42;

    // Pre-fill stack to desired size
    for (size_t i = 0; i < state.range(0); ++i) {
        stack_push(stack, &value);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(stack_push(stack, &value));
        state.PauseTiming();
        stack_pop(stack);  // Maintain constant size
        state.ResumeTiming();
    }

    stack_destroy(stack);
}
BENCHMARK(BM_StackPushSized)->Range(1 << 10, 1 << 20);

// Benchmark std::stack push performance at different sizes
static void BM_StdStackPushSized(benchmark::State &state) {
    std::stack<int> stack;

    // Pre-fill stack to desired size
    for (size_t i = 0; i < state.range(0); ++i) {
        stack.push(42);
    }

    for (auto _ : state) {
        stack.push(42);
        benchmark::DoNotOptimize(stack);
        state.PauseTiming();
        stack.pop();  // Maintain constant size
        state.ResumeTiming();
    }
}
BENCHMARK(BM_StdStackPushSized)->Range(1 << 10, 1 << 20);

BENCHMARK_MAIN();
