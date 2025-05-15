#include <benchmark/benchmark.h>

#include <queue>
#include <random>

#include "libdsc/queue.h"

// Benchmark size operation
static void BM_QueueSize(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));
    int value = 42;
    for (size_t i = 0; i < 1000; ++i) {
        queue_push(queue, &value);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(queue_size(queue));
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueueSize)->Range(1 << 10, 1 << 20);

// Benchmark std::queue size
static void BM_StdQueueSize(benchmark::State &state) {
    std::queue<int> queue;
    for (size_t i = 0; i < 1000; ++i) {
        queue.push(42);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(queue.size());
    }
}
BENCHMARK(BM_StdQueueSize)->Range(1 << 10, 1 << 20);

// Benchmark empty check
static void BM_QueueEmpty(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));

    for (auto _ : state) {
        benchmark::DoNotOptimize(queue_empty(queue));
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueueEmpty)->Range(1 << 10, 1 << 20);

// Benchmark std::queue empty
static void BM_StdQueueEmpty(benchmark::State &state) {
    std::queue<int> queue;

    for (auto _ : state) {
        benchmark::DoNotOptimize(queue.empty());
    }
}
BENCHMARK(BM_StdQueueEmpty)->Range(1 << 10, 1 << 20);

// Benchmark back access
static void BM_QueueBack(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));
    int value = 42;
    queue_push(queue, &value);

    for (auto _ : state) {
        benchmark::DoNotOptimize(queue_back(queue));
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueueBack)->Range(1 << 10, 1 << 20);

// Benchmark std::queue back access
static void BM_StdQueueBack(benchmark::State &state) {
    std::queue<int> queue;
    queue.push(42);

    for (auto _ : state) {
        benchmark::DoNotOptimize(queue.back());
    }
}
BENCHMARK(BM_StdQueueBack)->Range(1 << 10, 1 << 20);

// Benchmark clear operation
static void BM_QueueClear(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));
    int value = 42;

    for (auto _ : state) {
        state.PauseTiming();
        // Fill queue
        for (size_t i = 0; i < state.range(0); ++i) {
            queue_push(queue, &value);
        }
        state.ResumeTiming();

        queue_clear(queue);
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueueClear)->Range(1 << 10, 1 << 20);

// Benchmark std::queue clear equivalent
static void BM_StdQueueClear(benchmark::State &state) {
    std::queue<int> queue;

    for (auto _ : state) {
        state.PauseTiming();
        // Fill queue
        for (size_t i = 0; i < state.range(0); ++i) {
            queue.push(42);
        }
        state.ResumeTiming();

        while (!queue.empty()) {
            queue.pop();
        }
    }
}
BENCHMARK(BM_StdQueueClear)->Range(1 << 10, 1 << 20);

// Benchmark reserve operation
static void BM_QueueReserve(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));

    for (auto _ : state) {
        benchmark::DoNotOptimize(queue_reserve(queue, state.range(0)));
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueueReserve)->Range(1 << 10, 1 << 20);

// Benchmark push
static void BM_QueuePush(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));

    for (auto _ : state) {
        int value = 42;
        dsc_error result = queue_push(queue, &value);
        benchmark::DoNotOptimize(result);
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueuePush)->Range(1, 1 << 20);

// Benchmark std::queue push
static void BM_StdQueuePush(benchmark::State &state) {
    std::queue<int> queue;

    for (auto _ : state) {
        queue.push(42);
        benchmark::DoNotOptimize(queue);
    }
}
BENCHMARK(BM_StdQueuePush)->Range(1, 1 << 20);

// Benchmark push and pop
static void BM_QueuePushPop(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));

    for (auto _ : state) {
        int value = 42;
        dsc_error push_result = queue_push(queue, &value);
        dsc_error pop_result = queue_pop(queue);
        benchmark::DoNotOptimize(push_result);
        benchmark::DoNotOptimize(pop_result);
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueuePushPop)->Range(1, 1 << 20);

// Benchmark std::queue push and pop
static void BM_StdQueuePushPop(benchmark::State &state) {
    std::queue<int> queue;

    for (auto _ : state) {
        queue.push(42);
        queue.pop();
    }
}
BENCHMARK(BM_StdQueuePushPop)->Range(1, 1 << 20);

// Benchmark front access
static void BM_QueueFront(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));
    int value = 42;
    queue_push(queue, &value);

    for (auto _ : state) {
        void *front = queue_front(queue);
        benchmark::DoNotOptimize(front);
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueueFront)->Range(1 << 10, 1 << 20);

// Benchmark std::queue front access
static void BM_StdQueueFront(benchmark::State &state) {
    std::queue<int> queue;
    queue.push(42);

    for (auto _ : state) {
        benchmark::DoNotOptimize(queue.front());
    }
}
BENCHMARK(BM_StdQueueFront)->Range(1 << 10, 1 << 20);

// Benchmark push with pre-reserved capacity
static void BM_QueuePushReserved(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));
    queue_reserve(queue, state.range(0));
    int value = 42;

    for (auto _ : state) {
        state.PauseTiming();
        queue_clear(queue);
        state.ResumeTiming();

        for (size_t i = 0; i < state.range(0); ++i) {
            queue_push(queue, &value);
        }
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueuePushReserved)->Range(1 << 10, 1 << 20);

// Benchmark std::queue push with pre-reserved deque
static void BM_StdQueuePushReserved(benchmark::State &state) {
    std::queue<int> queue;

    for (auto _ : state) {
        state.PauseTiming();
        while (!queue.empty()) queue.pop();
        state.ResumeTiming();

        for (size_t i = 0; i < state.range(0); ++i) {
            queue.push(42);
        }
    }
}
BENCHMARK(BM_StdQueuePushReserved)->Range(1 << 10, 1 << 20);

// Benchmark alternating push/pop pattern
static void BM_QueueAlternating(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));
    queue_reserve(queue, state.range(0) / 2);  // Reserve half capacity
    int value = 42;
    bool push = true;

    for (auto _ : state) {
        if (push) {
            benchmark::DoNotOptimize(queue_push(queue, &value));
        } else {
            if (!queue_empty(queue)) {
                benchmark::DoNotOptimize(queue_pop(queue));
            }
        }
        push = !push;
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueueAlternating)->Range(1 << 10, 1 << 20);

// Benchmark std::queue alternating push/pop
static void BM_StdQueueAlternating(benchmark::State &state) {
    std::queue<int> queue;
    bool push = true;

    for (auto _ : state) {
        if (push) {
            queue.push(42);
            benchmark::DoNotOptimize(queue);
        } else {
            if (!queue.empty()) {
                queue.pop();
                benchmark::DoNotOptimize(queue);
            }
        }
        push = !push;
    }
}
BENCHMARK(BM_StdQueueAlternating)->Range(1 << 10, 1 << 20);

// Benchmark circular buffer behavior
static void BM_QueueCircularBuffer(benchmark::State &state) {
    dsc_queue *queue = queue_create(sizeof(int));
    queue_reserve(queue, state.range(0));
    int value = 42;

    // Fill queue to capacity
    for (size_t i = 0; i < state.range(0); ++i) {
        queue_push(queue, &value);
    }

    // Remove half elements
    for (size_t i = 0; i < state.range(0) / 2; ++i) {
        queue_pop(queue);
    }

    // Benchmark pushing more elements (should wrap around)
    for (auto _ : state) {
        benchmark::DoNotOptimize(queue_push(queue, &value));
        queue_pop(queue);  // Keep size constant
    }

    queue_destroy(queue);
}
BENCHMARK(BM_QueueCircularBuffer)->Range(1 << 10, 1 << 20);

// Benchmark std::queue wrap-around behavior
static void BM_StdQueueCircularBuffer(benchmark::State &state) {
    std::queue<int> queue;

    // Fill queue
    for (size_t i = 0; i < state.range(0); ++i) {
        queue.push(42);
    }

    // Remove half elements
    for (size_t i = 0; i < state.range(0) / 2; ++i) {
        queue.pop();
    }

    // Benchmark pushing more elements
    for (auto _ : state) {
        queue.push(42);
        benchmark::DoNotOptimize(queue);
        queue.pop();  // Keep size constant
    }
}
BENCHMARK(BM_StdQueueCircularBuffer)->Range(1 << 10, 1 << 20);

BENCHMARK_MAIN();
